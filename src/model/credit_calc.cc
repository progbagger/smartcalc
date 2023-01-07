#include "credit_calc.h"

std::vector<calculator::model::CreditCalculator::record_type>
calculator::model::CreditCalculator::Calculate(const Parameters& params) {
  double term = TermToMonths(params.term, params.term_type);
  double rate = RateToMonthly(params.rate, params.rate_type);
  std::vector<record_type> result;
  result.reserve(term + 2);
  result.push_back(record_type{params.sum, 0, 0, params.sum});
  if (params.credit_type == CreditType::kAnnuity)
    CalculateAnnuity(params.sum, term, rate, result);
  else
    CalculateDifferentiated(params.sum, term, rate, result);
  return result;
}

void calculator::model::CreditCalculator::PushRecord(
    double* sum, double* in_interest_total, double* in_payment_total,
    double rate, double monthly_payment, std::vector<record_type>& records) {
  double in_interest = *sum * rate;
  double in_payment = monthly_payment - in_interest;
  *in_interest_total += in_interest;
  *in_payment_total += in_payment;
  *sum -= in_payment;
  records.push_back(
      record_type{monthly_payment, in_payment, in_interest, *sum});
}

void calculator::model::CreditCalculator::CalculateAnnuity(
    double sum, std::size_t term, double rate,
    std::vector<record_type>& records) {
  double monthly_payment =
      sum * (rate / (1.0 - pow((1.0 + rate), -(double)term)));
  double in_interest_total = 0;
  double in_payment_total = 0;
  for (std::size_t i = 1; i < term + 1; ++i) {
    PushRecord(&sum, &in_interest_total, &in_payment_total, rate,
               monthly_payment, records);
  }
  records.push_back(record_type{in_payment_total + in_interest_total,
                                in_payment_total, in_interest_total, 0});
}

void calculator::model::CreditCalculator::CalculateDifferentiated(
    double sum, std::size_t term, double rate,
    std::vector<record_type>& records) {
  double rest = sum;
  double in_interest_total = 0;
  double in_payment_total = 0;
  for (std::size_t i = 1; i < term + 1; ++i) {
    double monthly_payment = sum / term + rest * rate;
    PushRecord(&rest, &in_interest_total, &in_payment_total, rate,
               monthly_payment, records);
  }
  records.push_back(record_type{in_payment_total + in_interest_total,
                                in_payment_total, in_interest_total, 0});
}
