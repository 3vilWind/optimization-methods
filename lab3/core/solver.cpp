#include <cstdio>
#include <filesystem>
#include <tuple>
#include <functional>
#include "generators/Utils.h"
#include "matrices/SymmetricProfileMatrix.h"
#include "matrices/Serializers.h"
#include "solvers/LUInPlaceSolver.h"
#include "solvers/GaussPivotingInPlaceSolver.h"
#include "solvers/VectorUtils.h"
#include "solvers/ConjugateGradientInPlaceSolver.h"

extern int iter;

std::tuple<double, double> getError(const std::vector<std::vector<double>> &results) {
    double absolute = 0;
    double relative = 0;
    auto expected = generateIncrementalVector(results[0].size());
    double expectedNorm = norm(expected);

    for (const auto &result : results) {
        double currentAbsolute = norm(subtract(expected, result));
        double currentRelative = currentAbsolute / expectedNorm;
        absolute += currentAbsolute;
        relative += currentRelative;
    }
    absolute /= results.size();
    relative /= results.size();

    return std::make_tuple(absolute, relative);
}


std::tuple<double, double, double>
getErrorExtended(const std::vector<std::vector<double>> &results, const std::vector<double> &discrepancy) {
    double absolute = 0;
    double relative = 0;
    double disc = 0;
    auto expected = generateIncrementalVector(results[0].size());
    double expectedNorm = norm(expected);

    for (int i = 0; i < results.size(); ++i) {
        double currentAbsolute = norm(subtract(expected, results[i]));
        double currentRelative = currentAbsolute / expectedNorm;
        absolute += currentAbsolute;
        relative += currentRelative;
        disc += currentRelative / discrepancy[i];
    }
    absolute /= results.size();
    relative /= results.size();
    disc /= results.size();

    return std::make_tuple(absolute, relative, disc);
}


void printDDMResults(const std::vector<std::vector<double>> &results, size_t n, size_t k) {
    auto[absolute, relative] = getError(results);

    printf("%u\t%u\t%e\t%e\n", n, k, absolute, relative);
}


void printHilbertResults(const std::vector<std::vector<double>> &results, size_t n) {
    auto[absolute, relative] = getError(results);

    printf("%u\t%e\t%e\n", n, absolute, relative);
}


void
printSDDMResults(const std::vector<std::vector<double>> &results, size_t n, const std::vector<double> &discrepancy) {
    auto[absolute, relative, disc] = getErrorExtended(results, discrepancy);
    printf("%u\t%d\t%e\t%e\t%e\n", n, iter, absolute, relative, disc);
}


void loadSPM(const std::filesystem::path &path, SymmetricProfileMatrix &a, std::vector<double> &b) {
    auto aPath = path;
    aPath.append("spm_a.dat");
    auto bPath = path;
    bPath.append("spm_b.dat");

    deserialize(a, aPath.string());
    deserialize(b, bPath.string());
}


void loadDense(const std::filesystem::path &path, DenseMatrix &a, std::vector<double> &b) {
    auto aPath = path;
    aPath.append("dense_a.dat");
    auto bPath = path;
    bPath.append("dense_b.dat");

    deserialize(a, aPath.string());
    deserialize(b, bPath.string());
}


void loadSparse(const std::filesystem::path &path, SymmetricSparseRowColumnMatrix &a, std::vector<double> &b) {
    auto aPath = path;
    aPath.append("sparse_a.dat");
    auto bPath = path;
    bPath.append("sparse_b.dat");

    deserialize(a, aPath.string());
    deserialize(b, bPath.string());
}


std::tuple<std::vector<double>, double> loadSparseSolveByCG(const std::filesystem::path &path) {
    SymmetricSparseRowColumnMatrix a;
    std::vector<double> b;
    loadSparse(path, a, b);

    ConjugateGradientInPlaceSolver conjugateGradientInPlaceSolver;
    auto x = conjugateGradientInPlaceSolver.solve(a, b, 1e-7);
    auto ax = generateB(a, x);
    double discrepancy = norm(subtract(b, ax)) / norm(b);
    return std::make_tuple(x, discrepancy);
}


std::vector<double> loadSPMSolveByLU(const std::filesystem::path &path) {
    SymmetricProfileMatrix a;
    std::vector<double> b;
    loadSPM(path, a, b);

    LUInPlaceSolver luInPlaceSolver;
    return luInPlaceSolver.solve(a, b, 0);
}


std::vector<double> loadDenseSolveByGauss(const std::filesystem::path &path) {
    DenseMatrix a;
    std::vector<double> b;
    loadDense(path, a, b);

    GaussPivotingInPlaceSolver gaussPivotingInPlaceSolver;
    return gaussPivotingInPlaceSolver.solve(a, b, 0);
}

typedef std::function<std::vector<double>(const std::filesystem::path &)> LoadSolve;


void loadSolveSDDM(std::filesystem::path path, bool invertSignOffDiagonal) {
    std::string p("symmetric_diagonally_dominant");
    p += (invertSignOffDiagonal ? "_inv" : "");
    path.append(p);

    std::vector<size_t> ns{10, 100, 1000};

    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        std::vector<std::vector<double>> results;
        std::vector<double> disc;
        for (int i = 0; i < 10; ++i) {
            auto fullPath = path;
            fullPath.append(std::to_string(n) + "_" + std::to_string(i));
            auto[x, discrepancy] = loadSparseSolveByCG(fullPath);
            results.emplace_back(x);
            disc.emplace_back(discrepancy);

        }
        printSDDMResults(results, n, disc);
    }
}


void loadSolveDDM(std::filesystem::path path, const LoadSolve &loadSolve) {
    path.append("diagonally_dominant");

    std::vector<size_t> ns{10, 100, 1000};
    std::vector<size_t> ks{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        for (size_t k: ks) {
            std::vector<std::vector<double>> results;
            for (int i = 0; i < 10; ++i) {
                auto fullPath = path;
                fullPath.append(std::to_string(n) + "_" + std::to_string(k) + "_" + std::to_string(i));

                results.emplace_back(loadSolve(fullPath));
            }
            printDDMResults(results, n, k);
        }
    }
}


void loadSolveHilbert(std::filesystem::path path, const LoadSolve &loadSolve) {
    path.append("hilbert");

    std::vector<size_t> ns{3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 100, 1000};

    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        std::vector<std::vector<double>> results;
        for (int i = 0; i < 10; ++i) {
            auto fullPath = path;
            fullPath.append(std::to_string(n) + "_" + std::to_string(i));

            results.emplace_back(loadSolve(fullPath));
        }
        printHilbertResults(results, n);
    }
}


void loadSolveSparseHilbert(std::filesystem::path path) {
    path.append("hilbert");

    std::vector<size_t> ns{10, 20, 30, 40, 50, 100, 200, 300, 400, 500, 1000};

    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        std::vector<std::vector<double>> results;
        std::vector<double> disc;
        for (int i = 0; i < 10; ++i) {
            auto fullPath = path;
            fullPath.append(std::to_string(n) + "_" + std::to_string(i));
            auto[x, discrepancy] = loadSparseSolveByCG(fullPath);
            results.emplace_back(x);
            disc.emplace_back(discrepancy);
        }
        printSDDMResults(results, n, disc);
    }
}


int main() {
    std::filesystem::path basePath = "./linear_systems/";
    loadSolveDDM(basePath, loadDenseSolveByGauss);
    loadSolveSparseHilbert(basePath);
    loadSolveSDDM(basePath, true);
    return 0;
}
