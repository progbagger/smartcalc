#include "credit_calculator_tests.h"

inline double GetSum(const credit_calculator_test_case_type& test_case) {
  return std::get<0>(test_case.first);
}

inline std::size_t GetTerm(const credit_calculator_test_case_type& test_case) {
  return std::get<1>(test_case.first);
}

inline s21::model::TermType GetTermType(
    const credit_calculator_test_case_type& test_case) {
  return std::get<2>(test_case.first);
}

inline double GetRate(const credit_calculator_test_case_type& test_case) {
  return std::get<3>(test_case.first);
}

inline s21::model::RateType GetRateType(
    const credit_calculator_test_case_type& test_case) {
  return std::get<4>(test_case.first);
}

inline s21::model::CreditCalculator::CreditType GetCreditType(
    const credit_calculator_test_case_type& test_case) {
  return std::get<5>(test_case.first);
}

inline s21::model::CreditCalculator::Parameters CreateParameters(
    const credit_calculator_test_case_type& test_case) {
  s21::model::CreditCalculator::Parameters params;
  params.sum = GetSum(test_case);
  params.term = GetTerm(test_case);
  params.term_type = GetTermType(test_case);
  params.rate = GetRate(test_case);
  params.rate_type = GetRateType(test_case);
  params.credit_type = GetCreditType(test_case);
  return params;
}

inline const std::string ParamsMsg(
    const credit_calculator_test_case_type& test_case) {
  return std::string(kNoteMsg) +
         " Failure at input:\nSum = " + std::to_string(GetSum(test_case)) +
         "\nTerm = " + std::to_string(GetTerm(test_case)) +
         "\nTerm type = " + std::to_string(GetTermType(test_case)) +
         "\nRate = " + std::to_string(GetRate(test_case)) +
         "\nRate type = " + std::to_string(GetRateType(test_case)) +
         "\nCredit type = " + std::to_string(GetCreditType(test_case));
}

inline void TestCreditCalculatorOneCase(
    const credit_calculator_test_case_type& test_case) {
  s21::model::CreditCalculator calculator;
  s21::model::CreditCalculator::Parameters params = CreateParameters(test_case);
  credit_calculator_test_result_type results = calculator.Calculate(params);
  ASSERT_EQ(results.size(), test_case.second.size() + 1)
      << ParamsMsg(test_case);
  // Testing first row
  ASSERT_EQ(results.at(0).size(), test_case.second.at(0).size())
      << ParamsMsg(test_case);
  EXPECT_NEAR(results.at(0).at(0), GetSum(test_case), kPrecision)
      << ParamsMsg(test_case);
  EXPECT_NEAR(results.at(0).at(1), 0, kPrecision) << ParamsMsg(test_case);
  EXPECT_NEAR(results.at(0).at(2), 0, kPrecision) << ParamsMsg(test_case);
  EXPECT_NEAR(results.at(0).at(3), GetSum(test_case), kPrecision)
      << ParamsMsg(test_case);
  // Testing other rows
  for (std::size_t i = 0; i < test_case.second.size(); ++i) {
    ASSERT_EQ(results.at(i + 1).size(), test_case.second.at(i).size())
        << ParamsMsg(test_case);
    for (std::size_t j = 0; j < test_case.second.at(i).size(); ++j) {
      ASSERT_NEAR(results.at(i + 1).at(j), test_case.second.at(i).at(j),
                  kPrecision)
          << ParamsMsg(test_case);
    }
  }
}

TEST(CreditCalculator, Annuity) {
  for (const auto& test_case : kAnnuityTestCases)
    TestCreditCalculatorOneCase(test_case);
}

TEST(CreditCalculator, Differentiated) {
  for (const auto& test_case : kDifferentiatedTestCases)
    TestCreditCalculatorOneCase(test_case);
}