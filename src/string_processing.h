#ifndef SRC_STRING_PROCESSING_H_
#define SRC_STRING_PROCESSING_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_digit(char c);
char *strestr(const char *haystack, const char *needle);
char *str_input();
char *simplify(const char *str);
char *strip(const char *str);
char *str_push(char *str, const char c);
char *str_free(char *str);
char *normalize_double(char *str);

#endif  // SRC_STRING_PROCESSING_H_
