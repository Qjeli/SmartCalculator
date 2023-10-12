#include "s21_smartcalc.h"

double s21_calculator(char *str, double x) {
  double result = 0;
  numbers *num_stack = NULL;
  operators *oper_stack = NULL;

  if (strlen(str) != 0) {
    parser(str, x, &num_stack, &oper_stack);
    result = count_result(&num_stack, &oper_stack);

    while (num_stack) {
      pop_numbers(&num_stack);
    }

    while (oper_stack) {
      pop_operators(&oper_stack);
    }
  }
  return result;
}

int is_sign(int i, char *str) {
  int result = 0;

  if ((str[i] == '-' && i == 0) || (str[i] == '(' && str[i + 1] == '-')) {
    result = 1;
  }

  if ((str[i] == '+' && i == 0) || (str[i] == '(' && str[i + 1] == '+')) {
    result = 1;
  }

  return result;
}

void parser(char *str, double x, numbers **num_stack, operators **oper_stack) {
  char num_tmp[255] = "";
  int i = 0;
  int j = 0;
  int str_len = 0;
  double num = 0;
  const char operators_arr[] = "+-*/^mcstal()";
  str_len = strlen(str);

  while (i < str_len) {
    while (is_number(str[i])) {
      num_tmp[j] = str[i];
      j++;
      i++;
    }

    if (!is_number(str[i]) && j > 0) {
      to_number(num_tmp, &num);
      push_numbers(num_stack, num);
      memset(&num_tmp, 0, sizeof(num_tmp));
      j = 0;
    }
    if (str[i] == 'x' || str[i] == 'X') {
      push_numbers(num_stack, x);
    }
    if (strchr(operators_arr, str[i]) != NULL) {
      parse_operator(str, &i, oper_stack, num_stack);
    }
    if (is_sign(i, str)) {
      push_numbers(num_stack, 0);
    }
    i++;
  }
}

int is_number(char c) {
  int result = 0;

  if ((c >= '0' && c <= '9') || c == '.' || c == ',' || c == 'e') {
    result = 1;
  } else {
    result = 0;
  }

  return result;
}

void to_number(char *str, double *num) {
  *num = 0;
  *num = atof(str);
}

void push_priority(int *i, operators **oper_stack, numbers **num_stack, int n,
                   int oper, int priority, int req_nums) {
  init_calc(num_stack, oper_stack, priority);

  if (priority != brac_close) {
    push_operators(oper_stack, oper, priority, req_nums);
  }
  *i += n - 1;
}

int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack) {
  int result = 0;

  //  operators
  if (str[*i] == '+') push_priority(i, oper_stack, num_stack, 1, '+', plus, 2);
  if (str[*i] == '-') push_priority(i, oper_stack, num_stack, 1, '-', minus, 2);
  if (str[*i] == '*') push_priority(i, oper_stack, num_stack, 1, '*', mult, 2);
  if (str[*i] == '/') push_priority(i, oper_stack, num_stack, 1, '/', DIV, 2);
  if (str[*i] == '^') push_priority(i, oper_stack, num_stack, 1, '^', EXP, 2);

  //  functions
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd')
    push_priority(i, oper_stack, num_stack, 3, 'm', mod, 2);
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's')
    push_priority(i, oper_stack, num_stack, 3, 'c', funcs, 1);
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n')
    push_priority(i, oper_stack, num_stack, 3, 's', funcs, 1);
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n')
    push_priority(i, oper_stack, num_stack, 3, 't', funcs, 1);
  if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's')
    push_priority(i, oper_stack, num_stack, 4, 'C', funcs, 1);
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
      str[*i + 3] == 'n')
    push_priority(i, oper_stack, num_stack, 4, 'S', funcs, 1);
  if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
      str[*i + 3] == 'n')
    push_priority(i, oper_stack, num_stack, 4, 'T', funcs, 1);
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't')
    push_priority(i, oper_stack, num_stack, 4, 'q', funcs, 1);
  if (str[*i] == 'l' && str[*i + 1] == 'n')
    push_priority(i, oper_stack, num_stack, 2, 'l', funcs, 1);
  if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g')
    push_priority(i, oper_stack, num_stack, 3, 'g', funcs, 1);

  //  brackets
  if (str[*i] == '(')
    push_priority(i, oper_stack, num_stack, 1, '(', brac_open, 1);
  if (str[*i] == ')')
    push_priority(i, oper_stack, num_stack, 1, ')', brac_close, 1);

  return result;  // why int when could be void
}