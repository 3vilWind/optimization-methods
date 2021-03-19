#include <emscripten/bind.h>

#include "core/methods/Dichotomy.h"
#include "core/OptimizationMethodDetailedResults.h"
#include "core/Point.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(point) {
        value_object<Point>("Point")
                .field("x", &Point::x)
                .field("y", &Point::y);
}

EMSCRIPTEN_BINDINGS(named_shape_points) {
        value_object<OptimizationMethodDetailedResults::NamedShapePoints>("NamedShapePoints")
                .field("name", &OptimizationMethodDetailedResults::NamedShapePoints::name)
                .field("points", &OptimizationMethodDetailedResults::NamedShapePoints::points);
}

EMSCRIPTEN_BINDINGS(optimization_method_detailed_results) {
        value_object<OptimizationMethodDetailedResults>("OptimizationMethodDetailedResults")
                .field("result", &OptimizationMethodDetailedResults::result)
                .field("iterations", &OptimizationMethodDetailedResults::iterations);
}

EMSCRIPTEN_BINDINGS(dichotomy) {
        emscripten::class_<Dichotomy>("Dichotomy")
                .constructor<void*>()
                .function("minimize", &Dichotomy::minimize);
}
