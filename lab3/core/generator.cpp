#include <cstdio>
#include <filesystem>
#include "generators/DiagonallyDominantGenerator.h"
#include "generators/HilbertGenerator.h"
#include "generators/Utils.h"
#include "matrices/SymmetricProfileMatrix.h"
#include "matrices/Serializers.h"
#include <functional>


void saveSPM(const DenseMatrix &a, const std::vector<double> &b, const std::filesystem::path &path) {
    auto aPath = path;
    aPath.append("spm_a.dat");
    auto bPath = path;
    bPath.append("spm_b.dat");

    serialize(SymmetricProfileMatrix(a), aPath.string());
    serialize(b, bPath.string());
}


void saveDense(const DenseMatrix &a, const std::vector<double> &b, const std::filesystem::path &path) {
    auto aPath = path;
    aPath.append("dense_a.dat");
    auto bPath = path;
    bPath.append("dense_b.dat");

    serialize(a, aPath.string());
    serialize(b, bPath.string());
}

typedef std::function<void(const DenseMatrix &, const std::vector<double> &,
                           const std::filesystem::path &)> SaveFunction;


void generateDiagonallyDominant(std::filesystem::path type_path, const SaveFunction &save) {
    type_path.append("diagonally_dominant");

    std::vector<size_t> ns{10, 100, 1000};
    std::vector<size_t> ks{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        for (size_t k: ks) {
            for (int i = 0; i < 10; ++i) {
                auto a = generateDiagonallyDominantMatrix(n, k);
                auto b = generateB(a, expectedResult);

                auto path = type_path;
                path.append(std::to_string(n) + "_" + std::to_string(k) + "_" + std::to_string(i));

                std::filesystem::create_directories(path);

                save(a, b, path);

                printf("Generated DDM n=%u k=%u\n", n, k);
            }

        }
    }
}


void generateHilbert(std::filesystem::path type_path, const SaveFunction &save) {
    type_path.append("hilbert");

    std::vector<size_t> ns{3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 100, 1000};

    for (size_t n: ns) {
        for (int i = 0; i < 10; ++i) {
            auto expectedResult = generateIncrementalVector(n);
            auto a = generateHilbertMatrix(n);
            auto b = generateB(a, expectedResult);

            auto path = type_path;
            path.append(std::to_string(n) + "_" + std::to_string(i));

            std::filesystem::create_directories(path);

            save(a, b, path);

            printf("Generated Hilbert n=%u\n", n);
        }
    }
}


int main() {
    std::filesystem::path basePath = "./linear_systems/";
    generateDiagonallyDominant(basePath, saveSPM);
    generateHilbert(basePath, saveSPM);

    generateDiagonallyDominant(basePath, saveDense);
    generateHilbert(basePath, saveDense);

    return 0;
}
