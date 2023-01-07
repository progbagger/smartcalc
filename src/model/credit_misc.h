#ifndef MODEL_CREDIT_MISC_H_
#define MODEL_CREDIT_MISC_H_

#include <vector>

namespace s21 {

namespace model {

enum TermType { kMonths, kYears, kDays };
enum RateType { kPerMonth, kPerAnnum };

inline std::size_t TermToMonths(std::size_t term, TermType term_type) {
  if (term_type == TermType::kMonths) return term;
  return term * 12;
}

inline double RateToMonthly(double rate, RateType rate_type) {
  if (rate_type == RateType::kPerMonth) return rate / 100;
  return rate / (100 * 12);
}

inline long double RateToPerAnnum(long double rate, RateType rate_type) {
  if (rate_type == RateType::kPerAnnum) return rate / 100;
  return (rate * 12) / 100;
}

}  // namespace model

}  // namespace s21

#endif  // MODEL_CREDIT_MISC_H_