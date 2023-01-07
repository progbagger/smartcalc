#include "date.h"

calculator::model::Date::Date()
    : day_(1), month_(1), year_(1), is_correct_(true) {}

calculator::model::Date::Date(int day, int month, int year)
    : day_(day), month_(month), year_(year) {
  ValidateDate();
}

calculator::model::Date::Date(const Date& other) { *this = other; }

calculator::model::Date& calculator::model::Date::operator=(const Date& other) {
  if (this != &other) {
    day_ = other.day_;
    month_ = other.month_;
    year_ = other.year_;
    is_correct_ = other.is_correct_;
    ValidateDate();
  }
  return *this;
}

calculator::model::Date::Date(const std::initializer_list<int>& items) {
  *this = items;
}

calculator::model::Date& calculator::model::Date::operator=(
    const std::initializer_list<int>& items) {
  if (items.size() < 3) {
    is_correct_ = false;
  } else {
    auto iter = items.begin();
    day_ = *iter;
    ++iter;
    month_ = *iter;
    ++iter;
    year_ = *iter;
    ValidateDate();
  }
  return *this;
}

int calculator::model::Date::GetDay() const { return day_; }

int calculator::model::Date::GetMonth() const { return month_; }

int calculator::model::Date::GetYear() const { return year_; }

bool calculator::model::Date::IsCorrect() const { return is_correct_; }

bool calculator::model::Date::IsYearLeap() const {
  return (!(year_ % 4) && year_ % 100) || !(year_ % 400);
}

void calculator::model::Date::IncreaseDay(int day) {
  day_ += day;
  while (day_ > GetMaxDay()) {
    day_ -= GetMaxDay();
    IncreaseMonth();
  }
}

void calculator::model::Date::IncreaseWeek(int weeks) {
  IncreaseDay(weeks * 7);
}

void calculator::model::Date::IncreaseMonth(int month) {
  month_ += month;
  int year_diff = (month_ - 1) / 12;
  month_ = (month_ - 1) % 12 + 1;
  IncreaseYear(year_diff);
}

void calculator::model::Date::IncreaseQuarter(int quarters) {
  IncreaseMonth(quarters * 3);
}

void calculator::model::Date::IncreaseHalf(int halfs) {
  IncreaseMonth(halfs * 6);
}

void calculator::model::Date::IncreaseYear(int year) {
  year_ += year;
  ValidateDate();
}

bool calculator::model::Date::operator==(const Date& other) const {
  return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool calculator::model::Date::operator!=(const Date& other) const {
  return !(*this == other);
}

bool calculator::model::Date::operator<(const Date& other) const {
  if (year_ < other.year_) return true;
  if (year_ > other.year_) return false;
  if (month_ < other.month_) return true;
  if (month_ > other.month_) return false;
  if (day_ < other.day_) return true;
  return false;
}

bool calculator::model::Date::operator<=(const Date& other) const {
  return *this < other || *this == other;
}

bool calculator::model::Date::operator>(const Date& other) const {
  return !(*this <= other);
}

bool calculator::model::Date::operator>=(const Date& other) const {
  return !(*this < other);
}

calculator::model::Date calculator::model::Date::GetCorrectDate() const {
  if (IsCorrect()) return *this;
  return Date(GetMaxDay(), GetMonth(), GetYear());
}

int calculator::model::Date::DaysTo(const Date& other) const {
  if (other <= *this) return 0;
  int result = 0;
  Date date(*this);
  while (!(date.GetYear() == other.GetYear() &&
           date.GetMonth() == other.GetMonth())) {
    result += date.GetMaxDay();
    date.IncreaseMonth();
  }
  result += other.GetDay() - date.GetDay();
  return result;
}

std::string calculator::model::Date::ToString() const {
  std::string result;
  if (GetDay() < 10) result += '0';
  result += std::to_string(GetDay());
  result += '.';
  if (GetMonth() < 10) result += '0';
  result += std::to_string(GetMonth());
  result += '.';
  result += std::to_string(GetYear());
  return result;
}

int calculator::model::Date::GetMaxDay() const {
  if (month_ == 2 && IsYearLeap()) return kDayCounts[month_ - 1] + 1;
  return kDayCounts[month_ - 1];
}

void calculator::model::Date::ValidateDate() {
  is_correct_ = day_ > 0 && month_ > 0 && month_ <= 12 && year_ > 0 &&
                day_ <= GetMaxDay();
}