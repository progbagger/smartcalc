#ifndef MODEL_DEPOSIT_CALC_H_
#define MODEL_DEPOSIT_CALC_H_

#include <array>
#include <cmath>
#include <list>

#include "credit_misc.h"
#include "date.h"

namespace s21 {

namespace model {

class DepositCalculator {
 public:
  using payment_type = std::pair<Date, long double>;
  using payment_list = std::list<payment_type>;
  using record_type = std::pair<Date, std::array<long double, 3>>;
  using return_type = std::vector<record_type>;

  enum PeriodicityType {
    kDaily,
    kWeekly,
    kMonthly,
    kPerQuarter,
    kPerHalfOfYear,
    kPerYear,
    kAtTheEnd
  };

  struct Parameters {
    long double sum;
    std::size_t term;
    TermType term_type;
    Date term_start;
    long double rate;
    RateType rate_type;
    PeriodicityType periodicity_of_payments;
    bool capitalization_of_interest;
    payment_list refills;
    payment_list withdrawals;
    long double minimum_rest;
  };

  DepositCalculator() = default;

  return_type Calculate(const Parameters& params);

 private:
  Date GetEndDate(const Date& start, int term, TermType term_type);
  void IncreaseDate(Date& date, PeriodicityType periodicity,
                    const Date& end_date);

  void UpdateIncome(long double* income, long double rest, long double rate,
                    const Date& previous_date, const Date& next_date);

  const payment_type* ChoosePayment(long double* change,
                                    const payment_type* refill,
                                    const payment_type* withdrawal);
  void ManageRefillsAndWithdrawals(std::vector<record_type>& result,
                                   long double* rest, long double* income,
                                   long double rate, long double minimum,
                                   Date& previous_date, Date& current_date,
                                   payment_list& refills,
                                   payment_list& withdrawals);
  void ClearPayment(const payment_type* payment, const payment_type** refill,
                    const payment_type** withdrawal);

  const payment_type* CheckPaymentsList(const Date& start_date,
                                        const Date& next_date,
                                        payment_list& payments_list);
};

}  // namespace model

}  // namespace s21

#endif  // MODEL_DEPOSIT_CALC_H_