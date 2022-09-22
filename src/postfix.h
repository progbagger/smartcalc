#ifndef SRC_POSTFIX_H_
#define SRC_POSTFIX_H_

#include "defines.h"
#include "string_processing.h"

typedef struct {
  char op;
  int priority;
} Operator;

Operator add_operator(const char op);
char *infix_to_postfix(const char *str);
char *calc_postfix(const char *str, double x);

#endif  // SRC_POSTFIX_H_
