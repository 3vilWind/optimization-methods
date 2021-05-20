cmake_minimum_required(VERSION 3.19)
project(linear_systems)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(code_tests solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h tests/SymmetricProfileMatrixTests.cpp tests/Utils.h)

target_link_libraries(
        code_tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(code_tests)


add_executable(linear_systems solver.cpp solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h generators/symmetric_profile/HilbertGenerator.cpp generators/symmetric_profile/HilbertGenerator.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h)

add_executable(generator generator.cpp solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h generators/symmetric_profile/HilbertGenerator.cpp generators/symmetric_profile/HilbertGenerator.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h generators/Generator.cpp generators/Generator.h generators/symmetric_profile/DiagonallyDominantGenerator.cpp generators/symmetric_profile/DiagonallyDominantGenerator.h matrices/SparseRowColumnMatrix.cpp matrices/SparseRowColumnMatrix.h generators/sparse_row_column/SimpleGenerator.cpp generators/sparse_row_column/SimpleGenerator.h generators/sparse_row_column/DiagonallyDominantGenerator.cpp generators/sparse_row_column/DiagonallyDominantGenerator.h generators/sparse_row_column/HilbertGenerator.cpp generators/sparse_row_column/HilbertGenerator.h generators/sparse_row_column/InverseSignGenerator.cpp generators/sparse_row_column/InverseSignGenerator.h generator.cpp)
