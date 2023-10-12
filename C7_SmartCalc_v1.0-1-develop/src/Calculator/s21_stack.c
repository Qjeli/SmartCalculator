#include "s21_smartcalc.h"

void push_numbers(numbers **top, double x) {
  numbers *tmp = NULL;
  tmp = (numbers *)calloc(1, sizeof(numbers));
  tmp->num = x;
  if (*top == NULL) {
    tmp->size = 1;
    tmp->next_numbers = NULL;
    *top = tmp;
  } else {
    tmp->size = (*top)->size + 1;
    tmp->next_numbers = *top;
    *top = tmp;
  }
}

void pop_numbers(numbers **top) {
  if (*top != NULL) {
    numbers *tmp = *top;
    (*top)->size = -1;
    *top = (*top)->next_numbers;
    free(tmp);
  }
}

void push_operators(operators **top, int opr, int priority,
                    int required_numbers) {
  operators *tmp = NULL;
  tmp = (operators *)calloc(1, sizeof(operators));
  tmp->operation = opr;
  tmp->priority = priority;
  tmp->required_numbers = required_numbers;

  if (*top == NULL) {
    tmp->next_operators = NULL;
    tmp->size = 1;
    *top = tmp;
  } else {
    tmp->size = (*top)->size + 1;
    tmp->next_operators = *top;
    *top = tmp;
  }
}

int pop_operators(operators **top) {
  int result = 0;

  if (*top != NULL) {
    if ((*top)->next_operators == NULL) {
      free(*top);
      *top = NULL;
    } else {
      operators *tmp = *top;
      (*top)->size -= 1;
      *top = (*top)->next_operators;
      free(tmp);
    }
  }
  return result;  // Why int???
}