#ifndef TESTS_DATE_TESTS_H_
#define TESTS_DATE_TESTS_H_

#include <gtest/gtest.h>

#include <vector>

#include "date.h"
#include "tests_misc.h"

using date_test_case_storage = std::vector<s21::model::Date>;

using date_comparsion_test_case = std::pair<s21::model::Date, s21::model::Date>;

using date_comparsion_test_case_storage =
    std::vector<date_comparsion_test_case>;

inline const date_test_case_storage kCorrectTestCases{
    {1, 1, 1984}, {31, 12, 2022}, {29, 2, 2024}, {28, 2, 2023}, {1, 1, 1}};

inline const date_test_case_storage kIncorrectTestCases{
    {29, 2, 2023}, {0, 0, 0}, {0, 1, 2022}, {31, 4, 2020}, {-1, -1, -1}};

inline const date_comparsion_test_case_storage kEqualDatesTestCases{
    {{12, 12, 2024}, {12, 12, 2024}},
    {{1, 1, 32}, {1, 1, 32}},
    {{999, 999, 999}, {999, 999, 999}},
    {{31, 12, 2022}, {31, 12, 2022}}};

inline const date_comparsion_test_case_storage kNotEqualDatesTestCases{
    {{12, 12, 2022}, {13, 12, 2022}},
    {{12, 12, 2022}, {12, 11, 2022}},
    {{12, 12, 2022}, {12, 12, 2023}}};

inline const date_comparsion_test_case_storage kLessDatesTestCases{
    {{1, 12, 2022}, {2, 12, 2022}},
    {{1, 11, 2022}, {31, 12, 2022}},
    {{31, 12, 2022}, {1, 1, 2023}}};

inline const date_comparsion_test_case_storage kLessOrEqualDatesTestCases{
    {{1, 12, 2022}, {2, 12, 2022}},  {{1, 11, 2022}, {31, 12, 2022}},
    {{31, 12, 2022}, {1, 1, 2023}},  {{12, 12, 2024}, {12, 12, 2024}},
    {{1, 1, 32}, {1, 1, 32}},        {{999, 999, 999}, {999, 999, 999}},
    {{31, 12, 2022}, {31, 12, 2022}}};

inline const date_comparsion_test_case_storage kGreaterDatesTestCases{
    {{2, 12, 2022}, {1, 12, 2022}},
    {{31, 12, 2022}, {1, 11, 2022}},
    {{1, 1, 2023}, {31, 12, 2022}}};

inline const date_comparsion_test_case_storage kGreaterOrEqualDatesTestCases{
    {{2, 12, 2022}, {1, 12, 2022}},  {{31, 12, 2022}, {1, 11, 2022}},
    {{1, 1, 2023}, {31, 12, 2022}},  {{12, 12, 2024}, {12, 12, 2024}},
    {{1, 1, 32}, {1, 1, 32}},        {{999, 999, 999}, {999, 999, 999}},
    {{31, 12, 2022}, {31, 12, 2022}}};

inline const std::string DateMsg(const s21::model::Date& date);

inline const std::string DatePairMsg(const s21::model::Date& date1,
                                     const s21::model::Date& date2);

inline void TestIncreaseFunction(const s21::model::Date& date,
                                 const s21::model::Date& date_compare,
                                 void (s21::model::Date::*function)(int),
                                 int value = 1, bool is_correct = true);

inline void TestIncreaseDay(const s21::model::Date& date,
                            const s21::model::Date& date_compare, int days = 1);

inline void TestIncreaseWeek(const s21::model::Date& date,
                             const s21::model::Date& date_compare,
                             int weeks = 1);

inline void TestIncreaseMonth(const s21::model::Date& date,
                              const s21::model::Date& date_compare,
                              int months = 1, bool is_correct = true);

inline void TestIncreaseQuarter(const s21::model::Date& date,
                                const s21::model::Date& date_compare,
                                int quarters = 1, bool is_correct = true);

inline void TestIncreaseHalf(const s21::model::Date& date,
                             const s21::model::Date& date_compare,
                             int halfs = 1, bool is_correct = true);

inline void TestIncreaseYear(const s21::model::Date& date,
                             const s21::model::Date& date_compare,
                             int years = 1, bool is_correct = true);

using date_days_to_test_case =
    std::tuple<s21::model::Date, s21::model::Date, int>;

using date_days_to_test_case_storage = std::vector<date_days_to_test_case>;

inline const date_days_to_test_case_storage kDaysToTestCases{
    {{1, 1, 2022}, {31, 1, 2022}, 30}, {{31, 1, 2022}, {1, 2, 2022}, 1},
    {{1, 1, 2022}, {1, 1, 2023}, 365}, {{1, 1, 2024}, {1, 1, 2025}, 366},
    {{1, 1, 2022}, {31, 12, 2021}, 0}, {{28, 2, 2023}, {1, 3, 2023}, 1},
    {{30, 4, 2023}, {1, 5, 2023}, 1},  {{1, 2, 2023}, {2, 5, 2023}, 90}};

inline const std::string DateDaysToMsg(const date_days_to_test_case& test_case);

inline void TestDaysTo(const date_days_to_test_case& test_case);

#endif  // TESTS_DATE_TESTS_H_