#include "s21_smartcalc.h"

void get_numbers(numbers **num_stack, double *a, double *b,
                 int required_numbers) {
  *b = (*num_stack)->num;
  pop_numbers(num_stack);

  if (required_numbers == 2) {
    *a = (*num_stack)->num;
    pop_numbers(num_stack);
  }
}

double calculator(double a, double b, operators *oper_stack) {
  double result = 0;

  if (oper_stack->operation == '+') {
    result = a + b;
  } else if (oper_stack->operation == '-') {
    result = a - b;
  } else if (oper_stack->operation == '*') {
    result = a * b;
  } else if (oper_stack->operation == '/') {
    result = a / b;
  } else if (oper_stack->operation == '^') {
    result = pow(a, b);
  } else if (oper_stack->operation == 'm') {
    result = fmod(a, b);
  } else if (oper_stack->operation == 'c') {
    result = cos(b);
  } else if (oper_stack->operation == 's') {
    result = sin(b);
  } else if (oper_stack->operation == 't') {
    result = tan(b);
  } else if (oper_stack->operation == 'C') {
    result = acos(b);
  } else if (oper_stack->operation == 'S') {
    result = asin(b);
  } else if (oper_stack->operation == 'T') {
    result = atan(b);
  } else if (oper_stack->operation == 'q') {
    result = sqrt(b);
  } else if (oper_stack->operation == 'l') {
    result = log(b);
  } else if (oper_stack->operation == 'g') {
    result = log10(b);
  }

  return result;
}

double count_result(numbers **num_stack, operators **oper_stack) {
  double a = 0;
  double b = 0;
  double result = 0;

  if ((*num_stack)->size == 1 && (*oper_stack) == NULL) {
    result = (*num_stack)->num;
  } else {
    while ((*oper_stack)->size != 1) {
      if ((*oper_stack)->priority == brac_open) {
        pop_operators(oper_stack);
      }
      get_numbers(num_stack, &a, &b, (*oper_stack)->required_numbers);
      result = calculator(a, b, *oper_stack);
      push_numbers(num_stack, result);

      if ((*oper_stack) != NULL) {
        pop_operators(oper_stack);
      }
    }
    if ((*oper_stack)->size == 1) {
      get_numbers(num_stack, &a, &b, (*oper_stack)->required_numbers);
      result = calculator(a, b, *oper_stack);
    } else {
      result = (*num_stack)->num;
    }
  }
  return result;
}

void init_calc(numbers **num_stack, operators **oper_stack, int priority) {
  double a = 0;
  double b = 0;
  int error = 0;

  if (*num_stack != NULL && priority != brac_open) {
    while ((*num_stack)->size >= 1 && *oper_stack != NULL &&
           priority <= (*oper_stack)->priority && !error) {
      if (priority == brac_close && (*oper_stack)->priority == brac_open) {
        pop_operators(oper_stack);
        error = 1;  // stop poping stack
      }
      if ((*oper_stack) != NULL && !error) {
        get_numbers(num_stack, &a, &b, (*oper_stack)->required_numbers);
        push_numbers(num_stack, calculator(a, b, *oper_stack));
        pop_operators(oper_stack);
      }
    }
  }
}