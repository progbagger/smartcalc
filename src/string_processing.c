#include "string_processing.h"

/**
 * @brief Function to check symbol on digit
 *
 * @param c Symbol to check
 * @return int 1 if digit; 0 otherwise
 */
int is_digit(char c) {
  int result = 0;
  if (c >= '0' && c <= '9') result = 1;
  return result;
}

/**
 * @brief Like strstr but checks if needle situated exactly
 * where haystack points
 *
 * @param haystack Where to search for the needle
 * @param needle String to search
 * @return char* If finded - pointer to finded string, haystack; if not - NULL
 */
char *strestr(const char *haystack, const char *needle) {
  char *result = (char *)strstr(haystack, needle);
  if (result != haystack) result = NULL;
  return result;
}

/**
 * @brief Function to push symbol into string
 *
 * @param str String where to push symbol
 * @param c Symbol to push
 * @return char* Pointer to destination string
 */
char *str_push(char *str, const char c) {
  if (str != NULL) {
    char *p = str;
    str = (char *)realloc(p, (strlen(str) + 2) * sizeof(char));
    str[strlen(str) + 1] = '\0';
    str[strlen(str)] = c;
  } else {
    str = (char *)malloc(2 * sizeof(char));
    str[1] = '\0';
    str[0] = c;
  }
  return str;
}

/**
 * @brief Function to free string
 *
 * @param str String to free
 * @return char* Nulling pointer to string
 */
char *str_free(char *str) {
  if (str) free(str);
  return NULL;
}

char *strip(const char *str) {
  char *result = NULL;
  while (*str) {
    if (*str != ' ') result = str_push(result, *str);
    str++;
  }
  return result;
}

/**
 * @brief Function to delete implicit spaces in given string (aka "strip")
 *
 * @param str String where to delete spaces
 * @return char* Pointer to a new string
 */
char *simplify(const char *str) {
  const char ops[] = "_=^+-*/()";
  char *result = NULL;
  char *str_without_spaces = strip(str);
  if (str_without_spaces) {
    int i = 0;
    int brackets_count = 0;
    char prev_op = '\0';
    while (str_without_spaces[i]) {
      // Creating arrays of function names and symbols to
      // reduce amount of code needed to parse string
      const char *funcs_str[] = {"sin",  "cos",  "tan", "asin", "acos",
                                 "atan", "sqrt", "mod", "log",  "ln"};
      const char *funcs_sym = "SCTsctqmLl";
      const size_t funcs_count = 10;
      int is_func_pushed = 0;
      for (size_t iter = 0; iter < funcs_count; iter++) {
        if (strestr(str_without_spaces + i, funcs_str[iter])) {
          if (str_without_spaces[i] != 'm' &&
              (is_digit(prev_op) || prev_op == 'x' || prev_op == 'y'))
            result = str_push(result, '*');
          result = str_push(result, funcs_sym[iter]);
          i += strlen(funcs_str[iter]) - 1;
          is_func_pushed = 1;
          break;
        }
      }
      if (!is_func_pushed) {
        // Unary operators handler
        if (strchr("-+", str_without_spaces[i]) &&
            (i == 0 || ((!is_digit(str_without_spaces[i - 1]) &&
                         str_without_spaces[i - 1] != 'x' &&
                         str_without_spaces[i - 1] != 'y') &&
                        str_without_spaces[i - 1] != ')'))) {
          if (str_without_spaces[i] == '-')
            result = str_push(result, '_');
          else
            result = str_push(result, '=');
        } else if ((is_digit(  // x, digits and dot handler
                        str_without_spaces[i]) ||
                    (str_without_spaces[i] == '.' &&
                     str_without_spaces[i + 1] != '.') ||
                    strchr(ops, str_without_spaces[i]) ||
                    str_without_spaces[i] == 'x' ||
                    str_without_spaces[i] == 'y') &&
                   !(i != 0 && str_without_spaces[i] == '.' &&
                     !is_digit(str_without_spaces[i - 1])) &&
                   !(i == 0 && str_without_spaces[i] == '.') &&
                   !(str_without_spaces[i] == '.' &&
                     !is_digit(str_without_spaces[i + 1]))) {
          if (str_without_spaces[i] == '(')
            brackets_count++;
          else if (str_without_spaces[i] == ')')
            brackets_count--;
          if ((is_digit(prev_op) && (str_without_spaces[i] == 'x' ||
                                     str_without_spaces[i] == 'y')) ||
              (prev_op == 'x' &&
               (is_digit(str_without_spaces[i]) ||
                str_without_spaces[i] == 'x' || str_without_spaces[i] == 'y')))
            result = str_push(result, '*');
          result = str_push(result, str_without_spaces[i]);
        } else {  // Error handler
          result = str_free(result);
          break;
        }
      }
      prev_op = str_without_spaces[i];
      i++;
    }
    str_free(str_without_spaces);
    if (brackets_count != 0) result = str_free(result);
  }
  return result;
}

/**
 * @brief Function to strip double numbers - cut off unwilling zeroes
 *
 * @param str Double number in string form
 * @return char* Pointer to stripped double number
 */
char *normalize_double(char *str) {
  char *end = str + strlen(str) - 1;
  while (*end == '0') {
    *end = '\0';
    end--;
  }
  if (*end == '.') *end = '\0';
  return str;
}
