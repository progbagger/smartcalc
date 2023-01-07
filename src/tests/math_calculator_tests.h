#ifndef TESTS_MATH_CALCULATOR_TESTS_H_
#define TESTS_MATH_CALCULATOR_TESTS_H_

#include <gtest/gtest.h>

#include <tuple>
#include <vector>

#include "math_calc.h"
#include "tests_misc.h"

constexpr double kError = 1e-10;

inline const std::string NoteWithExpression(const std::string& str);

inline void TestExpression(const std::string& expression,
                           bool expected_validation, double expected_result,
                           double x = NAN);

using math_calculator_test_case_type =
    std::tuple<const std::string, const bool, const double>;

using math_calculator_test_case_with_x_type =
    std::tuple<const std::string, const bool, const double, const double>;

using math_calculator_test_case_storage_type =
    const std::vector<math_calculator_test_case_type>;

using math_calculator_test_case_with_x_storage_type =
    const std::vector<math_calculator_test_case_with_x_type>;

inline math_calculator_test_case_storage_type kEasyTestCases{
    {"5", true, 5}, {"1e5", true, 1e5}, {"-1e20", true, -1e20}};

inline math_calculator_test_case_storage_type kUnaryOperatorTestCases{
    {"-0", true, 0},
    {"-2", true, -2},
    {"--2", false, NAN},
    {"0!", true, 1},
    {"1!", true, 1},
    {"2!", true, 2},
    {"3!", true, 6},
    {"3!!", true, 720},
    {"-1!", true, NAN},
    {"-+5", false, NAN},
    {"+-+-+---++88", false, NAN}};

inline math_calculator_test_case_storage_type kBinaryOperatorTestCases{
    {"3+2", true, 3 + 2},
    {"7-7", true, 7 - 7},
    {"5*25", true, 5 * 25},
    {"5/0", true, INFINITY},
    {"-5/0", true, -INFINITY},
    {"0/0", true, NAN},
    {"2^3", true, 8},
    {"2^3^2", true, 512},
    {"2*3+2", true, 2 * 3 + 2},
    {"2^2*5", true, pow(2, 2) * 5},
    {"1/5+2*8", true, 1.0 / 5.0 + 2 * 8},
    {"5%4", true, 5 % 4},
    {"5mod4", true, fmod(5, 4)},
    {"5fmod4", true, fmod(5, 4)},
    {"5%0", true, NAN},
    {"2*2^4", true, 2 * pow(2, 4)},
    {"2^4*2^4", true, pow(2, 4) * pow(2, 4)}};

inline math_calculator_test_case_storage_type kFunctionTestCases{
    {"sin(0)", true, sin(0)},
    {"cos(1)", true, cos(1)},
    {"sin(cos(3.1415))", true, sin(cos(3.1415))},
    {"tan(0)", true, tan(0)},
    {"tg(3.1415)", true, tan(3.1415)},
    {"ln(2.71)", true, log(2.71)},
    {"log(60)", true, log10(60)},
    {"log10(100)", false, NAN},
    {"log2(64)", false, NAN},
    {"ctg(sqrt(4))", true, 1.0 / (tan(sqrt(4)))},
    {"abs(-4)", true, fabs(-4)},
    {"sqrt(fabs(-64))", true, sqrt(fabs(-64))},
    {"exp(5)", true, exp(5)},
    {"fact(5)", true, 120},
    {"fact(-1)", true, NAN},
    {"asin(sin(1))", true, asin(sin(1))},
    {"acos(63)", true, acos(63)},
    {"atan(tan(2))", true, atan(tan(2))}};

inline math_calculator_test_case_storage_type kBracketTestCases{
    {"(0)", true, 0},    {"[-2]", true, 2},      {"(((((5)))))", true, 5},
    {"([-2])", true, 2}, {"([-2)]", false, NAN}, {"(5", false, NAN},
    {")(", false, NAN},  {"5)", false, NAN}};

inline math_calculator_test_case_with_x_storage_type kHardTests{
    {"sin([-x])*cos([-x])/atan(x)", true,
     sin(fabs(-4)) * cos(fabs(-4)) / atan(4), 4},
    {"acos(fabs(-x))*ln(log(2)*x)", true,
     acos(fabs(-0.7)) * log(log10(2) * 0.7), 0.7},
    {"ln(sin(sqrt(2*x^2+5*x)))", true,
     log(sin(sqrt(2 * pow(0.5, 2) + 5 * 0.5))), 0.5},
    {"log(3*sqrt(x)+6*sin(x)-7)", true, log10(3 * sqrt(22) + 6 * sin(22) - 7),
     22},
    {"3!*3!", true, 36, 0},
    {"+[-5]!*4^3.1415-sin(3.1415/2*tg(8.9*x))", true,
     120 * pow(4, 3.1415) - sin(3.1415 / 2 * tan(8.9 * 0.45)), 0.45}};

inline void TestAllCases(math_calculator_test_case_storage_type& test_cases);

inline void TestAllCases(
    math_calculator_test_case_with_x_storage_type& test_cases);

#endif  // TESTS_MATH_CALCULATOR_TESTS_H_