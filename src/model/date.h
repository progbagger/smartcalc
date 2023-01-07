#ifndef MODEL_DATE_H_
#define MODEL_DATE_H_

#include <initializer_list>
#include <string>

namespace calculator {

namespace model {

class Date {
 public:
  Date();
  Date(int day, int month, int year);
  Date(const Date& other);
  Date& operator=(const Date& other);

  Date(const std::initializer_list<int>& items);
  Date& operator=(const std::initializer_list<int>& items);

  int GetDay() const;
  int GetMonth() const;
  int GetYear() const;
  bool IsCorrect() const;

  bool IsYearLeap() const;

  void IncreaseDay(int day = 1);
  void IncreaseWeek(int weeks = 1);
  void IncreaseMonth(int month = 1);
  void IncreaseQuarter(int quarters = 1);
  void IncreaseHalf(int halfs = 1);
  void IncreaseYear(int year = 1);

  bool operator==(const Date& other) const;
  bool operator!=(const Date& other) const;
  bool operator<(const Date& other) const;
  bool operator<=(const Date& other) const;
  bool operator>(const Date& other) const;
  bool operator>=(const Date& other) const;

  Date GetCorrectDate() const;

  int DaysTo(const Date& other) const;

  std::string ToString() const;

 private:
  int day_;
  int month_;
  int year_;
  bool is_correct_;

  int GetMaxDay() const;

  void ValidateDate();

  const int kDayCounts[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

}  // namespace model

}  // namespace calculator

#endif  // MODEL_DATE_H_