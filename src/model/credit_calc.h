#ifndef MODEL_CREDIT_CALC_H_
#define MODEL_CREDIT_CALC_H_

#include <array>
#include <cmath>
#include <vector>

#include "credit_misc.h"

namespace s21 {

namespace model {

class CreditCalculator {
 public:
  using record_type = std::array<double, 4>;

  enum CreditType { kAnnuity, kDifferentiated };

  struct Parameters {
    double sum;
    std::size_t term;
    TermType term_type;
    double rate;
    RateType rate_type;
    CreditType credit_type;
  };

  CreditCalculator() = default;

  std::vector<record_type> Calculate(const Parameters& params);

 private:
  void CalculateAnnuity(double sum, std::size_t term, double rate,
                        std::vector<record_type>& records);
  void CalculateDifferentiated(double sum, std::size_t term, double rate,
                               std::vector<record_type>& records);
  void PushRecord(double* sum, double* in_interest_total,
                  double* in_payment_total, double rest, double monthly_payment,
                  std::vector<record_type>& records);
};

}  // namespace model

}  // namespace s21

#endif  // MODEL_CREDIT_CALC_H_