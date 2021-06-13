cmake_minimum_required(VERSION 3.19)
project(core)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../)
add_executable(core main.cpp
        ScalarFunction.h HypeOptimizationMethod.h
        methods/ClassicNewtonMethod.cpp methods/ClassicNewtonMethod.h

        ../../lab1/core/OptimizationMethodDetailedResults.h ../../lab1/core/OptimizationMethodDetailedResults.cpp
        ../../lab1/core/OptimizationMethod.h ../../lab1/core/OptimizationMethod.h
        ../../lab1/core/methods/Brent.h ../../lab1/core/methods/Brent.cpp
        ../../lab1/core/Utils.h ../../lab1/core/Utils.cpp

        ../../lab2/core/Vector.h ../../lab2/core/Vector.cpp
        ../../lab2/core/Utils.h ../../lab2/core/Utils.cpp
        ../../lab2/core/GradientMethod.h ../../lab2/core/GradientMethod.cpp
        ../../lab2/core/SquareMatrix.h ../../lab2/core/SquareMatrix.cpp
        ../../lab2/core/GradientMethodDetailedResult.h ../../lab2/core/GradientMethodDetailedResult.cpp
        ../../lab2/core/QuadraticFunction.h ../../lab2/core/QuadraticFunction.cpp
        ../../lab2/core/include/jacobi_pd.hpp

        ../../lab3/core/solvers/Solver.h ../../lab3/core/solvers/Solver.h
        ../../lab3/core/solvers/LUInPlaceSolver.h ../../lab3/core/solvers/LUInPlaceSolver.cpp
        ../../lab3/core/matrices/Matrix.h ../../lab3/core/matrices/Matrix.cpp
        ../../lab3/core/matrices/DenseMatrix.h ../../lab3/core/matrices/DenseMatrix.cpp
        ../../lab3/core/matrices/LUWrapperMatrix.h ../../lab3/core/matrices/LUWrapperMatrix.cpp

        methods/LinearSearchNewtonMethod.cpp methods/LinearSearchNewtonMethod.h
        methods/DescentNewtonMethod.cpp methods/DescentNewtonMethod.h
        methods/Utils.cpp methods/Utils.h
        ExampleFunctions.h
        methods/BfgshMethod.cpp methods/BfgshMethod.h
        methods/AbstractNewtonMethod.cpp methods/AbstractNewtonMethod.h
        methods/PowellMethod.cpp methods/PowellMethod.h
        methods/MarquardtMethod.cpp methods/MarquardtMethod.h
        methods/MarquardtCholeskyMethod.cpp methods/MarquardtCholeskyMethod.h)