#include "OptimizationMethodDetailedResults.h"

std::vector<OptimizationMethodDetailedResults::NamedShapePoints>
OptimizationMethodDetailedResults::getBorders(double x1, double y1, double x2, double y2) {
    return std::vector<OptimizationMethodDetailedResults::NamedShapePoints>({
                                                                                    {"left",  {Point(x1, y1)}},
                                                                                    {"right", {Point(x2, y2)}}
                                                                            });
}
