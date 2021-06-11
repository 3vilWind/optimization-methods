#include <lab4/core/HypeOptimizationMethod.h>

class MarquardtCholeskyMethod : public HypeOptimizationMethod {
public:
    HypeOptimizationResult minimize(const ScalarFunction &f, const Vector &startPoint, double epsilon) const override;

protected:
    bool isPositiveCholesky(DenseMatrix& matrix) const;
};
