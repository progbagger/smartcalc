#include "deposit_calc.h"

s21::model::DepositCalculator::return_type
s21::model::DepositCalculator::Calculate(const Parameters& params) {
  return_type result;
  long double rest = params.sum;
  long double rate = RateToPerAnnum(params.rate, params.rate_type);
  long double income_total = 0;
  Date end_date = GetEndDate(params.term_start, params.term, params.term_type);
  Date current_date = params.term_start;
  result.push_back({params.term_start, {NAN, rest, rest}});
  payment_list refills = params.refills;
  payment_list withdrawals = params.withdrawals;
  Date correct_date = current_date;
  while (current_date < end_date) {
    Date previous_date = correct_date;
    IncreaseDate(current_date, params.periodicity_of_payments, end_date);
    // if increasing on month we need to save maximum month to correctly display
    // days
    correct_date = current_date.GetCorrectDate();
    if (correct_date > end_date) correct_date = end_date;
    long double income = 0.0;
    ManageRefillsAndWithdrawals(result, &rest, &income, rate,
                                params.minimum_rest, previous_date,
                                current_date, refills, withdrawals);
    UpdateIncome(&income, rest, rate, previous_date, correct_date);
    income_total += income;
    if (params.capitalization_of_interest) rest += income;
    result.push_back(
        {correct_date,
         {income, params.capitalization_of_interest ? income : 0.0, rest}});
  }
  result.push_back({correct_date, {income_total, NAN, rest}});
  return result;
}

s21::model::Date s21::model::DepositCalculator::GetEndDate(const Date& start,
                                                           int term,
                                                           TermType term_type) {
  Date result(start);
  if (term_type == TermType::kDays)
    result.IncreaseDay(term);
  else if (term_type == TermType::kMonths)
    result.IncreaseMonth(term);
  else
    result.IncreaseYear(term);
  return result.GetCorrectDate();
}

void s21::model::DepositCalculator::IncreaseDate(Date& date,
                                                 PeriodicityType periodicity,
                                                 const Date& end_date) {
  switch (periodicity) {
    case PeriodicityType::kDaily:
      date.IncreaseDay();
      break;
    case PeriodicityType::kWeekly:
      date.IncreaseWeek();
      break;
    case PeriodicityType::kMonthly:
      date.IncreaseMonth();
      break;
    case PeriodicityType::kPerQuarter:
      date.IncreaseQuarter();
      break;
    case PeriodicityType::kPerHalfOfYear:
      date.IncreaseHalf();
      break;
    case PeriodicityType::kPerYear:
      date.IncreaseYear();
      break;
    default:
      date = end_date;
      break;
  }
}

void s21::model::DepositCalculator::UpdateIncome(long double* income,
                                                 long double rest,
                                                 long double rate,
                                                 const Date& previous_date,
                                                 const Date& next_date) {
  int term = previous_date.DaysTo(next_date);
  long double days_in_year = (next_date.IsYearLeap() ? 366.0 : 365.0);
  *income += rest * rate * (term / days_in_year);
}

const s21::model::DepositCalculator::payment_type*
s21::model::DepositCalculator::ChoosePayment(long double* change,
                                             const payment_type* refill,
                                             const payment_type* withdrawal) {
  if (refill && withdrawal && refill->first == withdrawal->first) {
    *change = refill->second + withdrawal->second;
    return refill;
  } else if ((!withdrawal && refill) ||
             (refill && withdrawal && refill->first < withdrawal->first)) {
    *change = refill->second;
    return refill;
  } else if ((!refill && withdrawal) ||
             (refill && withdrawal && refill->first > withdrawal->first)) {
    *change = withdrawal->second;
    return withdrawal;
  }
  return nullptr;
}

void s21::model::DepositCalculator::ManageRefillsAndWithdrawals(
    std::vector<record_type>& result, long double* rest, long double* income,
    long double rate, long double minimum, Date& previous_date,
    Date& current_date, payment_list& refills, payment_list& withdrawals) {
  const payment_type* refill = nullptr;
  const payment_type* withdrawal = nullptr;
  do {
    if (!refill)
      refill = CheckPaymentsList(previous_date, current_date, refills);
    if (!withdrawal)
      withdrawal = CheckPaymentsList(previous_date, current_date, withdrawals);
    if (refill || withdrawal) {
      long double current_change = 0;
      const payment_type* payment =
          ChoosePayment(&current_change, refill, withdrawal);
      if (*rest + current_change >= minimum) {
        // calculating income up to this moment
        UpdateIncome(income, *rest, rate, previous_date, payment->first);
        *rest += current_change;
        result.push_back({payment->first, {NAN, current_change, *rest}});
        // changing previous date to calculate correct income next time
        previous_date = payment->first;
      }
      // deleting payments that already processed
      ClearPayment(payment, &refill, &withdrawal);
    }
  } while (refill || withdrawal);
}

void s21::model::DepositCalculator::ClearPayment(
    const payment_type* payment, const payment_type** refill,
    const payment_type** withdrawal) {
  if (*refill && *withdrawal && (*refill)->first == (*withdrawal)->first) {
    delete *refill;
    *refill = nullptr;
    delete *withdrawal;
    *withdrawal = nullptr;
  } else if (payment == *refill) {
    delete *refill;
    *refill = nullptr;
  } else if (payment == *withdrawal) {
    delete *withdrawal;
    *withdrawal = nullptr;
  }
}

const s21::model::DepositCalculator::payment_type*
s21::model::DepositCalculator::CheckPaymentsList(const Date& start_date,
                                                 const Date& next_date,
                                                 payment_list& payments_list) {
  const payment_type* result = nullptr;
  for (auto payment = payments_list.begin(); payment != payments_list.end();
       ++payment) {
    if ((*payment).first >= start_date && (*payment).first <= next_date) {
      result = new payment_type(*payment);
      payments_list.erase(payment);
      break;
    }
  }
  return result;
}