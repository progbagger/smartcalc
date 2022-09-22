#ifndef SRC_CREDITS_H_
#define SRC_CREDITS_H_

#include <math.h>
#include <string.h>

int term_in_months(int value, const char *type);
double rate_in_monthly(double value, const char *type);
double annuity(double sum, double rate, const char *rate_type, int term,
               const char *term_type);
double differentiated(double sum, double ostatok, double rate,
                      const char *rate_type, int term, const char *term_type);

double calc_deposit(double sum, double rate, const char *rate_type, int term,
                    const char *term_type);

#endif  // SRC_CREDITS_H_
