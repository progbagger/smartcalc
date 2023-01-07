#include "math_calculator_tests.h"

inline const std::string NoteWithExpression(const std::string& str) {
  return std::string(kNoteMsg) + " Failure at \"" + str + "\"";
}

inline void TestExpression(const std::string& expression,
                           bool expected_validation, double expected_result,
                           double x) {
  calculator::model::MathCalculator calculator(expression);
  EXPECT_EQ(calculator.GetStatus(), expected_validation)
      << NoteWithExpression(expression);
  EXPECT_EQ(calculator.GetExpression(), expression)
      << NoteWithExpression(expression);
  if (std::isfinite(expected_result))
    EXPECT_NEAR(calculator.Calculate(x), expected_result, kError)
        << NoteWithExpression(expression);
  else if (std::isnan(expected_result))
    EXPECT_EQ(std::isnan(calculator.Calculate(x)), std::isnan(expected_result))
        << NoteWithExpression(expression);
  else
    EXPECT_EQ(std::isinf(calculator.Calculate(x)), std::isinf(expected_result))
        << NoteWithExpression(expression);
}

inline void TestAllCases(math_calculator_test_case_storage_type& test_cases) {
  for (const auto& test_case : test_cases) {
    TestExpression(std::get<0>(test_case), std::get<1>(test_case),
                   std::get<2>(test_case));
  }
}

inline void TestAllCases(
    math_calculator_test_case_with_x_storage_type& test_cases) {
  for (const auto& test_case : test_cases) {
    TestExpression(std::get<0>(test_case), std::get<1>(test_case),
                   std::get<2>(test_case), std::get<3>(test_case));
  }
}

TEST(MathCalculator, GetExpressionAndSetExpression) {
  calculator::model::MathCalculator calculator;
  EXPECT_TRUE(calculator.GetExpression().empty());

  calculator.SetExpression("aboba");
  EXPECT_EQ(calculator.GetExpression(), "aboba");
}

TEST(MathCalculator, GetStatus) {
  calculator::model::MathCalculator calculator("5");
  EXPECT_TRUE(calculator.GetStatus());

  calculator.SetExpression("aboba");
  EXPECT_FALSE(calculator.GetStatus());
}

TEST(MathCalculator, Easy) { TestAllCases(kEasyTestCases); }
TEST(MathCalculator, UnaryOperators) { TestAllCases(kUnaryOperatorTestCases); }
TEST(MathCalculator, BinaryOperators) {
  TestAllCases(kBinaryOperatorTestCases);
}
TEST(MathCalculator, Functions) { TestAllCases(kFunctionTestCases); }
TEST(MathCalculator, Brackets) { TestAllCases(kBracketTestCases); }
TEST(MathCalculator, Hard) { TestAllCases(kHardTests); }