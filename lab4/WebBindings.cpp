#include <emscripten/bind.h>
#include <sstream>
#include <string>
#include <vector>
#include "lab1/json.hpp"

#include "core/ScalarFunction.h"
#include "core/ExampleFunctions.h"
#include "core/methods/ClassicNewtonMethod.h"
#include "core/methods/LinearSearchNewtonMethod.h"
#include "core/methods/DescentNewtonMethod.h"
#include "core/methods/BfgshMethod.h"
#include "core/methods/PowellMethod.h"
#include "core/methods/MarquardtMethod.h"
#include "core/methods/MarquardtCholeskyMethod.h"


using json = nlohmann::json;

using namespace emscripten;

struct OptimizationCall {
    enum OptimizationMethodEnum {
        INVALID,
        CLASSIC_NEWTON,
        LINEAR_SEARCH_NEWTON,
        DESCENT_NEWTON,
        BFGSH,
        POWELL,
        MARQUARDT,
        MARQUARDT_CHOLESKY
    };

    ScalarFunction* function;
    OptimizationMethodEnum method;
    double epsilon;
    Vector* startPoint;
};

NLOHMANN_JSON_SERIALIZE_ENUM(OptimizationCall::OptimizationMethodEnum, {
    { OptimizationCall::OptimizationMethodEnum::INVALID, nullptr },
    { OptimizationCall::OptimizationMethodEnum::CLASSIC_NEWTON, "CLASSIC_NEWTON" },
    { OptimizationCall::OptimizationMethodEnum::LINEAR_SEARCH_NEWTON, "LINEAR_SEARCH_NEWTON" },
    { OptimizationCall::OptimizationMethodEnum::DESCENT_NEWTON, "DESCENT_NEWTON" },

    { OptimizationCall::OptimizationMethodEnum::BFGSH, "BFGSH" },
    { OptimizationCall::OptimizationMethodEnum::POWELL, "POWELL" },
    { OptimizationCall::OptimizationMethodEnum::MARQUARDT, "MARQUARDT" },
    { OptimizationCall::OptimizationMethodEnum::MARQUARDT_CHOLESKY, "MARQUARDT_CHOLESKY" }
})



void from_json(const json &j, OptimizationCall &p) {
    double startX, startY;
    std::string fun;
    p.method = j.at("method").get<OptimizationCall::OptimizationMethodEnum>();
    j.at("function").get_to(fun);

    j.at("startPoint").at("x").get_to(startX);
    j.at("startPoint").at("y").get_to(startY);

    j.at("epsilon").get_to(p.epsilon);

    ScalarFunction* f;

    if (fun == "F_1_1_1") {
        f = new F_1_1_1();
    } else if(fun == "F_1_1_2") {
        f = new F_1_1_2();
    } else if (fun == "F_1_2_1") {
        f = new F_1_2_1();
    } else if (fun == "F_1_2_2") {
        f = new F_1_2_2();
    } else if (fun == "F_2_1") {
        f = new F_2_1();
    } else if (fun == "F_2_2") {
        f = new F_2_2();
    } else if (fun == "F_2_3") {
        f = new F_2_3();
    } else if (fun == "F_2_4") {
        f = new F_2_4();
    } else {
        f = nullptr;
    }

    p.function = f;
    p.startPoint = new Vector(std::vector<double>({startX, startY}));
}


void to_json(json &j, const Vector &p) {
    j = json{{"x", p.get(0)},
             {"y", p.get(1)}};
}


void to_json(json &j, const HypeOptimizationResult &p) {
    j = json{{"result", p.result},
             {"iterations", p.iterations},
             {"additional", p.additional}};
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

    if (call.function == nullptr)
        return respondError("invalid function");

    HypeOptimizationMethod *method;
    switch (call.method) {
        case OptimizationCall::OptimizationMethodEnum::CLASSIC_NEWTON:
            method = new ClassicNewtonMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::LINEAR_SEARCH_NEWTON:
            method = new LinearSearchNewtonMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::DESCENT_NEWTON:
            method = new DescentNewtonMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::BFGSH:
            method = new BfgshMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::POWELL:
            method = new PowellMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::MARQUARDT:
            method = new MarquardtMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::MARQUARDT_CHOLESKY:
            method = new MarquardtCholeskyMethod();
            break;
        case OptimizationCall::OptimizationMethodEnum::INVALID:
            return respondError("invalid method");
    }

    auto a = method->minimize(*call.function, *call.startPoint, call.epsilon);
    delete method;
	delete call.function;
	delete call.startPoint;
    json result;
    to_json(result, a);
    return respondSuccess(result);
}

EMSCRIPTEN_BINDINGS(module) {
        function("callOptimizationMethod", &callOptimizationMethod);
}