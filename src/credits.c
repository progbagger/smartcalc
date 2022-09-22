#include "credits.h"

int term_in_months(int value, const char *type) {
  int result;
  if (!strcmp(type, "Years")) {
    result = value * 12;
  } else {
    result = value;
  }
  return result;
}

double rate_in_monthly(double value, const char *type) {
  double result;
  if (!strcmp(type, "Per annum"))
    result = value / (100.0 * 12.0);
  else
    result = value;
  return result;
}

double annuity(double sum, double rate, const char *rate_type, int term,
               const char *term_type) {
  rate = rate_in_monthly(rate, rate_type);
  int calculated_term = term_in_months(term, term_type);
  double result =
      sum * (rate / (1.0 - pow((1.0 + rate), (double)-calculated_term)));
  return result;
}

double differentiated(double sum, double ostatok, double rate,
                      const char *rate_type, int term, const char *term_type) {
  rate = rate_in_monthly(rate, rate_type);
  int calculated_term = term_in_months(term, term_type);
  double result = sum / (double)calculated_term +
                  ostatok * (rate * 12.0) / (double)calculated_term;
  return result;
}

double calc_deposit(double sum, double rate, const char *rate_type, int term,
                    const char *term_type) {
  if (!strcmp(rate_type, "Per annum"))
    rate /= 100.0;
  else
    rate *= 12.0;
  int calculated_term = term_in_months(term, term_type);
  double result = sum * pow((1.0 + rate / 12.0), calculated_term);
  return result;
}
