#include "postfix.h"

#include <math.h>

#include "stack.h"

/**
 * @brief Function to create an operator
 *
 * @param op Operator symbol
 * @return Operator with priority
 */
Operator add_operator(char op) {
  // * _ is unary minus
  // * = is unary plus
  // * m is mod
  Operator result;
  size_t i = 0;
  while (op != OPS[i]) i++;
  result.op = OPS[i];
  result.priority = PRI[i] - '0';
  return result;
}

/**
 * @brief Function to output full-length mathematical functions
 *
 * @param str String where to output function
 * @param op One-symbolic interpretation of mathematical function
 * @return char* Pointer to function string
 */
char *output_func(char *str, char op) {
  const char *funcs[] = {FUNCS};
  const char f_l[] = CHARF;
  size_t i = 0;
  while (f_l[i] != op) i++;
  for (size_t j = 0; j < strlen(funcs[i]); j++)
    str = str_push(str, funcs[i][j]);
  return str;
}

/**
 * @brief Function to output operands into string
 *
 * @param result Pointer to result string
 * @param str Pointer to string where to search for operands
 * @param i Current position in string str
 * @param operands Array with all possible operands
 * @return char* Pointer to result string
 */
char *handle_operand(char *result, const char *str, size_t *i,
                     const char *operands) {
  while (strchr(operands, str[*i]) && str[*i]) {
    result = str_push(result, str[*i]);
    ++(*i);
  }
  result = str_push(result, ' ');
  --(*i);
  return result;
}

/**
 * @brief Function to correctly handle parentheses occurences
 *
 * @param s Stack where to push elements
 * @param result Pointer to output string
 * @param funcs Array with all possible functions
 * @return char* Pointer to result string
 */
char *handle_close_bracket(Stack *s, char *result, const char *funcs) {
  Operator o = *((Operator *)pop_stack(s));
  while (o.op != '(') {
    result = str_push(result, o.op);
    result = str_push(result, ' ');
    if (!is_stack_empty(s))
      o = *((Operator *)pop_stack(s));
    else
      break;
  }
  Operator *top = (Operator *)top_stack(s);
  if (top) {
    if (strchr(funcs + 3, top->op)) {
      o = *((Operator *)pop_stack(s));
      result = output_func(result, o.op);
      result = str_push(result, ' ');
    }
  }
  return result;
}

/**
 * @brief Function to correctly handle operators occurences
 *
 * @param s Stack where to push values
 * @param result Pointer to result string
 * @param str Pointer to string where to search for operators
 * @param i Current position in string str
 * @param funcs Array with all possible functions
 * @return char* Pointer to result string
 */
char *handle_operator(Stack *s, char *result, const char *str, size_t i,
                      const char *funcs) {
  Operator *top = (Operator *)top_stack(s);
  Operator c_o = add_operator(str[i]);
  if (top) {
    while ((strchr(funcs + 3, top->op) || c_o.priority <= top->priority) &&
           !is_stack_empty(s) && !(c_o.op == '^' && top->op == '^')) {
      Operator o = *((Operator *)pop_stack(s));
      if (strchr(funcs + 3, o.op))
        result = output_func(result, o.op);
      else
        result = str_push(result, o.op);
      result = str_push(result, ' ');
      top = (Operator *)top_stack(s);
      if (!top) break;
    }
  }
  push_stack(s, (void *)&c_o, sizeof(Operator));
  return result;
}

/**
 * @brief Function to free allocated output string if something went wrong
 *
 * @param result Pointer to string to be freed
 * @return char* Pointer to freed string
 */
char *handle_error(char *result) {
  result = str_free(result);
  return result;
}

/**
 * @brief Function to correctly handle adding operators into stack
 *
 * @param s Stack where to push operators
 * @param str String where to get operator from
 * @param i Current position in string str
 */
void handle_func(Stack *s, const char *str, size_t i) {
  Operator o = add_operator(str[i]);
  push_stack(s, (void *)&o, sizeof(Operator));
}

/**
 * @brief Function to add last element into output string
 *
 * @param s Stack where to get last element
 * @param result Pointer to result string
 * @param funcs Array with all possible functions
 * @return char* Pointer to result string
 */
char *push_last(Stack *s, char *result, const char *funcs) {
  Operator o = *((Operator *)pop_stack(s));
  if (strchr(funcs + 3, o.op))
    result = output_func(result, o.op);
  else
    result = str_push(result, o.op);
  result = str_push(result, ' ');
  return result;
}

/**
 * @brief This function converts expression in infix notation into expression in
 * postfix notation and returns newly allocated string
 *
 * @param str Pointer to expression string which need to be converted
 * @return char* Pointer to converted string
 */
char *infix_to_postfix(const char *str) {
  char *result = NULL;
  char *normalized_str = simplify(str);
  const char ops[] = "^+-*m/";
  const char funcs[] = "_=(CSTcstqlL";
  const char operands[] = "0123456789.xy";
  Stack *s = init_stack();
  size_t i = 0;
  if (normalized_str) {
    while (normalized_str[i]) {
      if (strchr(operands, normalized_str[i])) {
        result = handle_operand(result, normalized_str, &i, operands);
      } else if (strchr(funcs, normalized_str[i])) {
        handle_func(s, normalized_str, i);
      } else if (normalized_str[i] == ')') {
        result = handle_close_bracket(s, result, funcs);
      } else if (strchr(ops, normalized_str[i])) {
        result = handle_operator(s, result, normalized_str, i, funcs);
      } else {
        result = handle_error(result);
        break;
      }
      i++;
    }
    while (!is_stack_empty(s) && result) result = push_last(s, result, funcs);
    if (result) result[strlen(result) - 1] = '\0';
  }
  str_free(normalized_str);
  destroy_stack(s);
  return result;
}

void skip_double(const char *str, size_t *pos) {
  while (str[*pos] >= '0' && str[*pos] <= '9') (*pos)++;
  if (str[*pos] == '.' && str[*pos + 1] >= '0' && str[*pos + 1] <= '9') {
    (*pos)++;
    while (str[*pos] >= '0' && str[*pos] <= '9') (*pos)++;
  }
}

/**
 * @brief Function to correctly handle adding of numbers to stack
 *
 * @param s Stack where to push numbers
 * @param str Pointer to string where to search numbers
 * @param i Current position in string str
 * @param x Double argument representing variable in mathematical expressions
 * @param operands Array with all possible operands
 * @return Stack* Pointer to stack where were pushed element
 */
Stack *calc_operand(Stack *s, const char *str, size_t *i, double x) {
  if (str[*i] == 'x' || str[*i] == 'y') {
    push_stack(s, (void *)&x, sizeof(double));
  } else {
    double number;
    sscanf(str + *i, "%lf", &number);
    skip_double(str, i);
    push_stack(s, (void *)&number, sizeof(double));
  }
  return s;
}

/**
 * @brief Function to correctly handle adding of operators to stack
 *
 * @param s Stack where to push values
 * @param str Pointer to string where to search for operators
 * @param i Current position in string str
 * @return Stack* Pointer to stack where were element pushed
 */
Stack *calc_operator(Stack *s, const char *str, size_t i) {
  double x2 = 0;
  double result;
  if (!is_stack_empty(s)) {
    x2 = *((double *)pop_stack(s));
  } else {
    s = destroy_stack(s);
  }
  if (s && !is_stack_empty(s)) {
    double x1 = *((double *)pop_stack(s));
    switch (str[i]) {
      case '+':
        result = x1 + x2;
        break;
      case '-':
        result = x1 - x2;
        break;
      case '/':
        result = x1 / x2;
        break;
      case '*':
        result = x1 * x2;
        break;
      case '^':
        result = pow(x1, x2);
        break;
      case 'm':
        result = fmod(x1, x2);
        break;
    }
  }
  if (s) push_stack(s, (void *)&result, sizeof(double));
  return s;
}

/**
 * @brief Function to correctly handle adding of mathematical functions to stack
 *
 * @param s Stack where to add elements
 * @param str Pointer to string where to search for elements
 * @param i Current position in string str
 * @return Stack* Pointer to stack where were element pushed
 */
Stack *calc_func(Stack *s, const char *str, size_t *i) {
  double result;
  if ((str[*i] == '_' || str[*i] == '=') && !is_stack_empty(s)) {
    result = *((double *)pop_stack(s));
    if (str[*i] == '_') result *= -1;
  } else if (!is_stack_empty(s)) {
    // Functions strings
    char *funcs_str[] = {FUNCS};
    // Functions pointers
    double (*funcs[])(double) = {cos,  sin,  tan, acos, asin,
                                 atan, sqrt, log, log10};
    // Functions count
    size_t funcs_count = 9;
    result = *((double *)pop_stack(s));
    for (size_t iter = 0; iter < funcs_count; iter++) {
      if (strestr(str + *i, funcs_str[iter])) {
        result = funcs[iter](result);
        (*i) += strlen(funcs_str[iter]) - 1;
        break;
      }
    }
    (*i)++;
  } else {
    s = destroy_stack(s);
  }
  if (s) push_stack(s, (void *)&result, sizeof(double));
  return s;
}

/**
 * @brief Function to calculate expression in postfix notation
 *
 * @param str Pointer to string with postfix notation expression
 * @param x Double parameter representing variable in mathematical expressions
 * @return double Result of expression
 */
char *calc_postfix(const char *str, double x) {
  char *result = NULL;
  if (str) {
    double double_result = NAN;
    const char operands[] = "0123456789xy";
    const char operators[] = "-+*/m^";
    const char funcs[] = "_=sincostanasinacosatansqrtmodlnlog";
    size_t i = 0;
    Stack *s = init_stack();
    while (str[i] && s) {
      if (strchr(operands, str[i])) {
        s = calc_operand(s, str, &i, x);
      } else if (strchr(operators, str[i])) {
        s = calc_operator(s, str, i);
      } else if (strchr(funcs, str[i])) {
        s = calc_func(s, str, &i);
      }
      i++;
    }
    if (s && !is_stack_empty(s)) {
      double_result = *((double *)pop_stack(s));
      destroy_stack(s);
    } else {
      s = destroy_stack(s);
    }
    if (s) {
      size_t buflen = 50;
      result = (char *)calloc(buflen, sizeof(char));
      snprintf(result, buflen, "%.8lf", double_result);
      result = normalize_double(result);
    }
  }
  return result;
}
