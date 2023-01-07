#include "date_tests.h"

inline const std::string DateMsg(const calculator::model::Date& date) {
  return std::string(kNoteMsg) + " Failure at \"" + date.ToString() + "\"";
}

TEST(Date, Correct) {
  for (const auto& test_case : kCorrectTestCases)
    EXPECT_TRUE(test_case.IsCorrect()) << DateMsg(test_case);
}

TEST(Date, Incorrect) {
  for (const auto& test_case : kIncorrectTestCases)
    EXPECT_FALSE(test_case.IsCorrect()) << DateMsg(test_case);
}

inline const std::string DatePairMsg(const calculator::model::Date& date1,
                                     const calculator::model::Date& date2) {
  return std::string(kNoteMsg) + " Failure at \"" + date1.ToString() +
         "\", \"" + date2.ToString() + "\"";
}

TEST(Date, Equal) {
  for (const auto& test_case : kEqualDatesTestCases)
    EXPECT_TRUE(test_case.first == test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

TEST(Date, NotEqual) {
  for (const auto& test_case : kNotEqualDatesTestCases)
    EXPECT_TRUE(test_case.first != test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

TEST(Date, Less) {
  for (const auto& test_case : kLessDatesTestCases)
    EXPECT_TRUE(test_case.first < test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

TEST(Date, LessOrEqual) {
  for (const auto& test_case : kLessOrEqualDatesTestCases)
    EXPECT_TRUE(test_case.first <= test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

TEST(Date, Greater) {
  for (const auto& test_case : kGreaterDatesTestCases)
    EXPECT_TRUE(test_case.first > test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

TEST(Date, GreaterOrEqual) {
  for (const auto& test_case : kGreaterOrEqualDatesTestCases)
    EXPECT_TRUE(test_case.first >= test_case.second)
        << DatePairMsg(test_case.first, test_case.second);
}

inline void TestIncreaseFunction(const calculator::model::Date& date,
                                 const calculator::model::Date& date_compare,
                                 void (calculator::model::Date::*function)(int),
                                 int value, bool is_correct) {
  calculator::model::Date date1(date);
  (date1.*function)(value);
  EXPECT_EQ(date1.IsCorrect(), is_correct) << DateMsg(date1);
  EXPECT_EQ(date1, date_compare) << DatePairMsg(date1, date_compare);
}

inline void TestIncreaseDay(const calculator::model::Date& date,
                            const calculator::model::Date& date_compare, int days) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseDay, days,
                       true);
}

TEST(Date, IncreaseDay) {
  TestIncreaseDay({1, 1, 2022}, {2, 1, 2022});
  TestIncreaseDay({31, 12, 2022}, {1, 1, 2023});
  TestIncreaseDay({27, 2, 2022}, {2, 3, 2022}, 3);
  TestIncreaseDay({31, 12, 2022}, {30, 5, 2023}, 150);
  TestIncreaseDay({31, 12, 2022}, {31, 12, 2023}, 365);
}

inline void TestIncreaseWeek(const calculator::model::Date& date,
                             const calculator::model::Date& date_compare, int weeks) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseWeek,
                       weeks, true);
}

TEST(Date, IncreaseWeek) {
  TestIncreaseWeek({1, 1, 2022}, {8, 1, 2022});
  TestIncreaseWeek({1, 1, 2022}, {15, 1, 2022}, 2);
  TestIncreaseWeek({31, 12, 2022}, {25, 2, 2023}, 8);
  TestIncreaseWeek({31, 12, 2022}, {15, 11, 2025}, 150);
  TestIncreaseWeek({1, 1, 2077}, {26, 6, 2364}, 15000);
}

inline void TestIncreaseMonth(const calculator::model::Date& date,
                              const calculator::model::Date& date_compare, int months,
                              bool is_correct) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseMonth,
                       months, is_correct);
}

TEST(Date, IncreaseMonth) {
  TestIncreaseMonth({1, 1, 2022}, {1, 2, 2022});
  TestIncreaseMonth({31, 1, 2022}, {31, 2, 2022}, 1, false);
  TestIncreaseMonth({31, 1, 2022}, {31, 1, 2023}, 12);
  TestIncreaseMonth({29, 2, 2024}, {29, 4, 2024}, 2);
  TestIncreaseMonth({29, 2, 2024}, {29, 2, 2028}, 48);
}

inline void TestIncreaseQuarter(const calculator::model::Date& date,
                                const calculator::model::Date& date_compare,
                                int quarters, bool is_correct) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseQuarter,
                       quarters, is_correct);
}

TEST(Date, IncreaseQuarter) {
  TestIncreaseQuarter({1, 1, 2022}, {1, 4, 2022});
  TestIncreaseQuarter({31, 12, 2022}, {31, 12, 2023}, 4);
  TestIncreaseQuarter({29, 2, 2024}, {29, 5, 2024}, 1);
}

inline void TestIncreaseHalf(const calculator::model::Date& date,
                             const calculator::model::Date& date_compare, int halfs,
                             bool is_correct) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseHalf,
                       halfs, is_correct);
}

TEST(Date, IncreaseHalf) {
  TestIncreaseHalf({1, 1, 2022}, {1, 7, 2022});
  TestIncreaseHalf({31, 12, 2022}, {31, 6, 2023}, 1, false);
}

inline void TestIncreaseYear(const calculator::model::Date& date,
                             const calculator::model::Date& date_compare, int years,
                             bool is_correct) {
  TestIncreaseFunction(date, date_compare, &calculator::model::Date::IncreaseYear,
                       years, is_correct);
}

TEST(Date, IncreaseYear) {
  TestIncreaseYear({1, 1, 2022}, {1, 1, 2023});
  TestIncreaseYear({31, 12, 2022}, {31, 12, 2032}, 10);
}

TEST(Date, Getters) {
  calculator::model::Date date(31, 12, 2022);
  EXPECT_EQ(date.GetDay(), 31);
  EXPECT_EQ(date.GetMonth(), 12);
  EXPECT_EQ(date.GetYear(), 2022);
}

TEST(Date, InitializerListIncorrect) {
  calculator::model::Date date1{1, 2, 3, 4, 5};
  EXPECT_EQ(date1.IsCorrect(), true);

  calculator::model::Date date2{1, 12};
  EXPECT_NE(date2.IsCorrect(), true);
}

TEST(Date, OperatorString) {
  calculator::model::Date date1(1, 1, 2022);
  EXPECT_EQ(date1.ToString(), "01.01.2022");

  calculator::model::Date date2(31, 12, 1984);
  EXPECT_EQ(date2.ToString(), "31.12.1984");
}

inline const std::string DateDaysToMsg(
    const date_days_to_test_case& test_case) {
  return std::string(kNoteMsg) + " Failure at \"" +
         std::get<0>(test_case).ToString() + "\" to \"" +
         std::get<1>(test_case).ToString() + "\" is " +
         std::to_string(std::get<2>(test_case));
}

inline void TestDaysTo(const date_days_to_test_case& test_case) {
  EXPECT_EQ(std::get<0>(test_case).DaysTo(std::get<1>(test_case)),
            std::get<2>(test_case))
      << DateDaysToMsg(test_case);
}

TEST(Date, DaysTo) {
  for (const auto& test_case : kDaysToTestCases) {
    TestDaysTo(test_case);
  }
}

TEST(Date, DefaultConstructor) {
  calculator::model::Date date;
  ASSERT_TRUE(date.IsCorrect());
  EXPECT_EQ(date.GetDay(), 1);
  EXPECT_EQ(date.GetMonth(), 1);
  EXPECT_EQ(date.GetYear(), 1);
}

TEST(Date, GetCorrectDate) {
  calculator::model::Date date(31, 2, 2022);
  ASSERT_FALSE(date.IsCorrect());
  ASSERT_EQ(date.GetCorrectDate(), calculator::model::Date(28, 2, 2022));
}