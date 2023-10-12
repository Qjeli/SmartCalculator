#include "s21_smartcalc.h"

int correct_dot(char *str) {
  int result = 0;
  int i = 0;
  int str_len = 0;
  int dot = 0;
  str_len = strlen(str);
  while (i < str_len) {
    if (str[0] == '.') {
      result = 1;
    }
    if (str[i] >= '0' && str[i] <= '9') {
      if (i + 1 < str_len && str[i + 1] == '.') {
        dot += 1;
      }
    } else {
      if (i + 1 < str_len && str[i + 1] == '.') {
        result = 1;
      }
    }
    if (dot > 1) {
      result = 1;
    }
    i++;
  }
  return result;
}

int brackets_incor(char *str) {
  int result = 0;
  int open_bracket = 0;
  int str_len = 0;
  str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == '(') {
      open_bracket++;
    }
    if (str[i] == ')') {
      open_bracket--;
    }
    if (str[i] == '(' && str[i + 1] == ')') {
      open_bracket = -5;
    }
  }

  if (open_bracket == 0) {
    result = 0;
  } else {
    result = 1;
  }

  return result;
}

int function_incor(char *str) {
  int result = 0;
  int str_len = 0;
  str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd' &&
        strchr("0123456789 -", str[i + 3]) != NULL) {  //  mod
      i += 3;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
               str[i + 3] == '(') {  //  cos
      i += 3;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
               str[i + 3] == '(') {  //  sin
      i += 3;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' &&
               str[i + 3] == '(') {  // tan
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's' && str[i + 4] == '(') {  //  acos
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {  //  asin
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {  //  atan
      i += 4;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't' && str[i + 4] == '(') {  //  sqrt
      i += 4;
    } else if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] == '(') {
      i += 2;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (strchr("+-*/^() xX", str[i]) == NULL && !is_number(str[i])) {
      result = 1;
    }
  }
  return result;
}

int lost_numbers(char *str) {
  int str_len = 0;
  str_len = strlen(str);
  int stop = 0;
  int result = 0;
  int i = 0;

  while (i < str_len && stop < 2) {
    if (strchr("+-*/^", str[i]) != NULL) stop++;
    if (strchr("0123456789xX(", str[i]) != NULL) stop = 0;
    if (str[i] == '(' && strchr("*/^m", str[i + 1]) != NULL) stop = 2;
    if ((str[i] == 'x' || str[i] == 'X') && is_number(str[i + 1])) stop = 2;
    if (is_number(str[i]) && (str[i + 1] == 'x' || str[i + 1] == 'X')) stop = 2;
    if (strchr("0123456789x", str[i]) != NULL && str[i + 1] == '(') stop = 2;
    i++;
  }
  if (strchr("0123456789x)", str[str_len - 1]) == NULL) stop = 1;

  if (stop) {
    result = 1;
  } else {
    result = 0;
  }

  return result;
}

int validation(char *str) {
  int i = 0;
  int error = 0;
  int result = 0;
  char number_tmp[255] = "";
  int j = 0;
  double num = 0;
  int str_len = 0;
  str_len = strlen(str);

  if (str_len > 255) error++;
  if (str_len == 1 && strchr("012356789", str[0]) == NULL) {
    error++;
  }

  error += brackets_incor(str);
  error += function_incor(str);
  error += lost_numbers(str);

  while (i < str_len && !error) {
    if (strchr("cstal0123456789(x+- ", str[0]) == NULL) {
      error += 1;
    }

    while (is_number(str[i])) {
      if (str[i] == ',') {
        str[i] = '.';
      }
      number_tmp[j] = str[i];
      j++;
      i++;
    }

    if (!is_number(str[i]) && j > 0) {
      to_number(number_tmp, &num);
      error += correct_dot(number_tmp);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
    i++;
  }
  if (str_len == 1 && (str[0] == 'x' || str[0] == 'X')) {
    error = 0;
  }

  if (error) {
    result = 0;
  } else {
    result = 1;
  }

  return result;
}