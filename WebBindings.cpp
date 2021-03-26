#include <emscripten/bind.h>
#include <sstream>
#include <string>
#include "json.hpp"

#include "core/methods/Dichotomy.h"
#include "core/methods/Fibonacci.h"
#include "core/methods/GoldenRatio.h"
#include "core/methods/Parabola.h"
#include "core/methods/Brent.h"

using json = nlohmann::json;

using namespace emscripten;

struct OptimizationCall {
    enum OptimizationMethodEnum {
        INVALID,
        DICHOTOMY,
        GOLDEN_RATIO,
        FIBONACCI,
        PARABOLA,
        BRENT
    };

    using Function = std::function<double(double)>;
    OptimizationMethodEnum method;
    std::function<double(double)> function;
    double left, right, epsilon;
};

NLOHMANN_JSON_SERIALIZE_ENUM(OptimizationCall::OptimizationMethodEnum, {
    { OptimizationCall::OptimizationMethodEnum::INVALID, nullptr },
    { OptimizationCall::OptimizationMethodEnum::DICHOTOMY, "DICHOTOMY" },
    { OptimizationCall::OptimizationMethodEnum::GOLDEN_RATIO, "GOLDEN_RATIO" },
    { OptimizationCall::OptimizationMethodEnum::FIBONACCI, "FIBONACCI" },
    { OptimizationCall::OptimizationMethodEnum::PARABOLA, "PARABOLA" },
    { OptimizationCall::OptimizationMethodEnum::BRENT, "BRENT" },
})

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OptimizationMethodDetailedResults, result, iterations)

void to_json(json &j, const OptimizationCall &p) {
    j = json{{"method",   p.method},
             {"function", reinterpret_cast<int>(p.function.target<double(double)>())},
             {"left",     p.left},
             {"right",    p.right},
             {"epsilon",  p.epsilon}};
}

void from_json(const json &j, OptimizationCall &p) {
    p.method = j.at("method").get<OptimizationCall::OptimizationMethodEnum>();
    int function = j.at("function");
    p.function = reinterpret_cast<double (*)(double)>(function);
    j.at("left").get_to(p.left);
    j.at("right").get_to(p.right);
    j.at("epsilon").get_to(p.epsilon);
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

    OptimizationMethod *method;
    switch (call.method) {
        case OptimizationCall::OptimizationMethodEnum::DICHOTOMY:
            method = new Dichotomy();
            break;
        case OptimizationCall::OptimizationMethodEnum::GOLDEN_RATIO:
            method = new GoldenRatio();
            break;
        case OptimizationCall::OptimizationMethodEnum::FIBONACCI:
            method = new Fibonacci();
            break;
        case OptimizationCall::OptimizationMethodEnum::PARABOLA:
            method = new Parabola();
            break;
        case OptimizationCall::OptimizationMethodEnum::BRENT:
            method = new Brent();
            break;
        case OptimizationCall::OptimizationMethodEnum::INVALID:
            return respondError("invalid method");
    }

    OptimizationMethodDetailedResults a = method->minimize(call.function, call.left, call.right, call.epsilon);
    delete method;
    json result;
    to_json(result, a);
    return respondSuccess(result);
}

EMSCRIPTEN_BINDINGS(module) {
        function("callOptimizationMethod", &callOptimizationMethod);
}