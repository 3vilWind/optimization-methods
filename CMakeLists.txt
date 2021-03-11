cmake_minimum_required(VERSION 3.17)
project(one_dimensional_optimization_methods)

set(CMAKE_CXX_STANDARD 14)

add_executable(one_dimensional_optimization_methods main.cpp OptimizationMethod.cpp OptimizationMethod.h OptimizationMethodDetailedResults.cpp OptimizationMethodDetailedResults.h Point.cpp Point.h methods/Dichotomy.cpp methods/Dichotomy.h methods/GoldenRatio.cpp methods/GoldenRatio.h methods/Fibonacci.cpp methods/Fibonacci.h methods/Parabola.cpp methods/Parabola.h methods/Brent.cpp methods/Brent.h)