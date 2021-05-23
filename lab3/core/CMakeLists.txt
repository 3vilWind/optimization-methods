cmake_minimum_required(VERSION 3.19)
project(linear_systems)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(code_tests solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h tests/SymmetricProfileMatrixTests.cpp tests/Utils.h matrices/LUWrapperMatrix.cpp matrices/LUWrapperMatrix.h tests/LUInPlaceSolverTests.cpp tests/Utils.cpp tests/SparseRowColumnTest.cpp tests/GaussPivotingInPlaceSolverTests.cpp matrices/SparseRowColumnMatrix.cpp matrices/SparseRowColumnMatrix.h tests/ConjugateGradientInPlaceSolverTests.cpp solvers/VectorUtils.h solvers/VectorUtils.cpp)

target_link_libraries(
        code_tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(code_tests)


add_executable(solver solver.cpp solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h matrices/LUWrapperMatrix.cpp matrices/LUWrapperMatrix.h generators/DiagonallyDominantGenerator.h generators/DiagonallyDominantGenerator.cpp generators/Utils.h generators/Utils.cpp solvers/VectorUtils.h solvers/VectorUtils.cpp matrices/SparseRowColumnMatrix.cpp matrices/SparseRowColumnMatrix.h)

add_executable(generator generator.cpp solvers/LUInPlaceSolver.cpp solvers/LUInPlaceSolver.h matrices/SymmetricProfileMatrix.cpp matrices/SymmetricProfileMatrix.h matrices/Matrix.cpp matrices/Matrix.h solvers/GaussPivotingInPlaceSolver.cpp solvers/GaussPivotingInPlaceSolver.h solvers/Solver.cpp solvers/Solver.h solvers/ConjugateGradientInPlaceSolver.cpp solvers/ConjugateGradientInPlaceSolver.h matrices/DenseMatrix.cpp matrices/DenseMatrix.h matrices/SparseRowColumnMatrix.cpp matrices/SparseRowColumnMatrix.h matrices/LUWrapperMatrix.cpp matrices/LUWrapperMatrix.h generators/DiagonallyDominantGenerator.h generators/DiagonallyDominantGenerator.cpp generators/HilbertGenerator.cpp generators/HilbertGenerator.h generators/Utils.cpp generators/Utils.h matrices/Serializers.h generators/SymmetricDiagonallyDominantGenerator.cpp generators/SymmetricDiagonallyDominantGenerator.h solvers/VectorUtils.h solvers/VectorUtils.cpp)
