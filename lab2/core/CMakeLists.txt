cmake_minimum_required(VERSION 3.17)
project(multi_dimensional_optimization_methods)

set(CMAKE_CXX_STANDARD 14)

set(LAB1_PATH "../../lab1")

include_directories(../../)

add_executable(multi_dimensional_optimization_methods main.cpp ${LAB1_PATH}/core/OptimizationMethod.cpp ${LAB1_PATH}/core/OptimizationMethod.h ${LAB1_PATH}/core/OptimizationMethodDetailedResults.cpp ${LAB1_PATH}/core/OptimizationMethodDetailedResults.h ${LAB1_PATH}/core/methods/Dichotomy.cpp ${LAB1_PATH}/core/methods/Dichotomy.h ${LAB1_PATH}/core/methods/GoldenRatio.cpp ${LAB1_PATH}/core/methods/GoldenRatio.h ${LAB1_PATH}/core/methods/Fibonacci.cpp ${LAB1_PATH}/core/methods/Fibonacci.h ${LAB1_PATH}/core/methods/Parabola.cpp ${LAB1_PATH}/core/methods/Parabola.h ${LAB1_PATH}/core/methods/Brent.cpp ${LAB1_PATH}/core/methods/Brent.h ${LAB1_PATH}/core/Utils.cpp ${LAB1_PATH}/core/Utils.h SquareMatrix.h Vector.cpp Vector.h methods/ConjugateGradientMethod.cpp methods/ConjugateGradientMethod.h methods/GradientDescent.cpp methods/GradientDescent.h methods/GradientSteepestDescent.cpp methods/GradientSteepestDescent.h GradientMethod.h GradientMethod.cpp GradientMethodDetailedResult.h GradientMethodDetailedResult.cpp Matrix.cpp Matrix.h DiagonalMatrix.cpp DiagonalMatrix.h SquareMatrix.cpp Utils.cpp Utils.h QuadraticFunction.cpp QuadraticFunction.h)

