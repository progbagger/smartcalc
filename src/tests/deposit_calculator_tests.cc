#include "deposit_calculator_tests.h"

inline const std::string PaymentListToString(
    const s21::model::DepositCalculator::payment_list& list) {
  std::string result;
  for (const auto& payment : list) {
    if (!result.empty()) result += "\n";
    result += "  {Date = " + payment.first.ToString() +
              ", payment = " + std::to_string(payment.second) + "}";
  }
  if (result.empty()) result = "  Empty";
  return result;
}

inline const std::string ParamsMsg(
    const deposit_calculator_test_case_type& test_case) {
  const s21::model::DepositCalculator::Parameters& params = test_case.first;
  return std::string(kNoteMsg) +
         " Failure at input:\nSum = " + std::to_string(params.sum) +
         "\nTerm = " + std::to_string(params.term) +
         "\nTerm type = " + std::to_string(params.term_type) +
         "\nTerm start = " + params.term_start.ToString() +
         "\nRate = " + std::to_string(params.rate) +
         "\nRate type = " + std::to_string(params.rate_type) +
         "\nPayment periodicity = " +
         std::to_string(params.periodicity_of_payments) +
         "\nCapitalization = " +
         std::to_string(params.capitalization_of_interest) +
         "\nRefills list:\n" + PaymentListToString(params.refills) +
         "\nWithdrawals list:\n" + PaymentListToString(params.withdrawals);
}

inline void TestDepositOneCase(
    const deposit_calculator_test_case_type& test_case) {
  s21::model::DepositCalculator calculator;
  s21::model::DepositCalculator::return_type test_result =
      calculator.Calculate(test_case.first);
  ASSERT_EQ(test_result.size(), test_case.second.size())
      << ParamsMsg(test_case);
  for (std::size_t i = 0; i < test_result.size(); ++i) {
    const std::array<long double, 3>& result_records = test_result.at(i).second;
    const std::array<long double, 3>& test_case_records =
        test_case.second.at(i).second;
    ASSERT_EQ(result_records.size(), test_case_records.size())
        << ParamsMsg(test_case);
    const s21::model::Date& result_date = test_result.at(i).first;
    const s21::model::Date& test_case_date = test_case.second.at(i).first;
    EXPECT_EQ(result_date, test_case_date) << ParamsMsg(test_case);
    test_case.second.at(i).second;
    for (std::size_t j = 0; j < result_records.size(); ++j) {
      if (std::isnan(test_case_records.at(j))) {
        ASSERT_EQ(std::isnan(result_records.at(j)),
                  std::isnan(test_case_records.at(j)))
            << ParamsMsg(test_case);
      } else {
        ASSERT_NEAR(result_records.at(j), test_case_records.at(j),
                    test_case.first.sum / 10000.0)
            << ParamsMsg(test_case);
      }
    }
  }
}

TEST(DepositCalculator, TestAll) {
  for (const auto& test_case : kAllTestCases) TestDepositOneCase(test_case);
}
