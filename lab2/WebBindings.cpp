#include <emscripten/bind.h>
#include <sstream>
#include <string>
#include "lab1/json.hpp"
#include "core/QuadraticFunction.h"
#include "core/Matrix.h"
#include "core/Vector.h"
#include <vector>
#include "core/GradientMethodDetailedResult.h"
#include "core/GradientMethod.h"
#include "core/methods/ConjugateGradientMethod.h"
#include "core/methods/GradientDescent.h"
#include "core/methods/GradientSteepestDescent.h"

using json = nlohmann::json;

using namespace emscripten;

struct OptimizationCall {
    enum OptimizationMethodEnum {
        INVALID,
        GRADIENT_DESCENT,
        GRADIENT_STEEPEST_DESCENT,
        CONJUGATE_GRADIENT_METHOD
    };

    QuadraticFunction* function;
    OptimizationMethodEnum method;
    double epsilon;
    Vector* startPoint;
};

NLOHMANN_JSON_SERIALIZE_ENUM(OptimizationCall::OptimizationMethodEnum, {
    { OptimizationCall::OptimizationMethodEnum::INVALID, nullptr },
    { OptimizationCall::OptimizationMethodEnum::GRADIENT_DESCENT, "GRADIENT_DESCENT" },
    { OptimizationCall::OptimizationMethodEnum::GRADIENT_STEEPEST_DESCENT, "GRADIENT_STEEPEST_DESCENT" },
    { OptimizationCall::OptimizationMethodEnum::CONJUGATE_GRADIENT_METHOD, "CONJUGATE_GRADIENT_METHOD" },
})


void from_json(const json &j, OptimizationCall &p) {
    double xx, xy, yy;
    double x, y, c;
    double startX, startY;
    p.method = j.at("method").get<OptimizationCall::OptimizationMethodEnum>();
    j.at("function").at("xx").get_to(xx);
    j.at("function").at("xy").get_to(xy);
    j.at("function").at("yy").get_to(yy);

    j.at("function").at("x").get_to(x);
    j.at("function").at("y").get_to(y);

    j.at("function").at("c").get_to(c);

    j.at("startPoint").at("x").get_to(startX);
    j.at("startPoint").at("y").get_to(startY);

    j.at("epsilon").get_to(p.epsilon);

    auto a = new Matrix(std::vector<Vector>({
        Vector(std::vector<double>({xx, xy})),
        Vector(std::vector<double>({xy, yy}))
    }));

    auto b = new Vector(std::vector<double>({x, y}));

    p.function = new QuadraticFunction(a, b, c);
    p.startPoint = new Vector(std::vector<double>({startX, startY}));
}


void to_json(json &j, const Vector &p) {
    j = json{{"x", p.get(0)},
             {"y", p.get(1)}};
}


void to_json(json &j, const GradientMethodDetailedResult &p) {
    j = json{{"result", p.result},
             {"iterations", p.iterations}};
}


std::string respondError(const std::string &message) {
    json result;
    result["message"] = message;
    result["success"] = 0;
    return result.dump();
}

std::string respondSuccess(json result) {
    result["success"] = 1;
    return result.dump();
}

std::string callOptimizationMethod(std::string request) {
    auto request_json = json::parse(request);
    OptimizationCall call;
    try {
        from_json(request_json, call);
    } catch (json::out_of_range &e) {
        return respondError(e.what());
    }

    GradientMethod *method;
    switch (call.method) {
        case OptimizationCall::OptimizationMethodEnum::GRADIENT_DESCENT:
            method = new GradientDescent();
            break;
        case OptimizationCall::OptimizationMethodEnum::GRADIENT_STEEPEST_DESCENT:
            method = new GradientSteepestDescent();
            break;
        case OptimizationCall::OptimizationMethodEnum::CONJUGATE_GRADIENT_METHOD:
            method = new ConjugateGradientMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::INVALID:
            return respondError("invalid method");
    }

    GradientMethodDetailedResult a = method->minimize(*call.function, *call.startPoint, call.epsilon);
    delete method;
    delete call.function->a;
    delete call.function->b;
	delete call.function;
	delete call.startPoint;
    json result;
    to_json(result, a);
    return respondSuccess(result);
}

EMSCRIPTEN_BINDINGS(module) {
        function("callOptimizationMethod", &callOptimizationMethod);
}