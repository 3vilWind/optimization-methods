#include <cstdio>
#include <filesystem>
#include "generators/DiagonallyDominantGenerator.h"
#include "generators/HilbertGenerator.h"
#include "generators/Utils.h"
#include "matrices/SymmetricProfileMatrix.h"
#include "matrices/Serializers.h"

int main() {
    std::filesystem::path basePath = "./linear_systems/";
    auto type_path = basePath;
    type_path.append("diagonally_dominant");

    std::vector<size_t> ns{10, 100, 1000};
    std::vector<size_t> ks{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (size_t n: ns) {
        auto expectedResult = generateIncrementalVector(n);
        for (size_t k: ks) {
            auto a = generateDiagonallyDominantMatrix(n, k);
            auto b = generateB(a, expectedResult);

            auto path = type_path;
            path.append(std::to_string(n) + "_" + std::to_string(k));

            std::filesystem::create_directories(path);

            auto aPath = path;
            aPath.append("a.dat");
            auto bPath = path;
            bPath.append("b.dat");

            SymmetricProfileMatrix spm(a);
            serialize(spm, aPath.string());
            serialize(b, bPath.string());

            printf("Generated DDM n=%u k=%u\n", n, k);
        }
    }

    return 0;
}
