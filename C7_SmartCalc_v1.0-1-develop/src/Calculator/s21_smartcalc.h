#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {  // assigning constatants

  plus,
  mult,
  minus = 1,
  DIV,
  mod = 2,
  EXP,
  funcs,
  brac_open = -1,
  brac_close = -2,
  annuity = 10,
  differ = 11,
  with_Capital = 12,
  without_Capital = 13,
  daily = 14,
  monthly = 15

};

typedef struct struct_numbers {
  double num;
  struct struct_numbers *next_numbers;
  int size;
} numbers;

typedef struct struct_operators {
  int operation;
  struct struct_operators *next_operators;
  int priority;
  int size;
  int required_numbers;
} operators;

typedef struct credit_struct {
  double monthly_Payment;
  double monthlyPaymentFrst;
  double monthlyPaymentLst;
  double over_Payment;
  double total_Payment;
} credit_Values;

typedef struct deposit_struct {
  double total_Interest;
  double tax_Amount;
  double final_Amount;
} deposit_Values;

typedef struct amount_change {
  int day;
  int month;
  int year;
  double sum;
} change_Values;

typedef struct date_struct {
  int day;
  int month;
  int year;
} date_Values;

// main
double s21_calculator(char *str, double x);
void get_numbers(numbers **num_stack, double *a, double *b, int req_nums);
double calculator(double a, double b, operators *oper_stack);
double count_result(numbers **num_stack, operators **oper_stack);
void init_calc(numbers **num_stack, operators **oper_stack, int priority);

// stack
void push_numbers(numbers **top, double x);
void pop_numbers(numbers **top);
void push_operators(operators **top, int opr, int prior, int required_nums);
int pop_operators(operators **top);

//  valivators
int validation(char *str);
int div_zero(int div, double num);
int correct_dot(char *str);
int brackets_incor(char *str);
int function_incor(char *str);
int lost_numbers(char *str);

//  parser
void parser(char *str, double, numbers **num_stack, operators **op_stack);
int is_number(char c);
void to_number(char *str, double *num);
int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack);
void push_operators(operators **top, int operation, int priority, int req_nums);
void push_priority(int *i, operators **oper_stack, numbers **num_stack, int n,
                   int oper, int priority, int req_nums);
int is_sign(int i, char *str);

// credit
credit_Values credit_calc(double amount, int time, double rate, int type);

// deposit
deposit_Values deposit_calc(double amount, int time, double rate, double tax,
                            int payment, int capital, char *change);
int change_Parcer(char *change, change_Values *amount_List);
double dailyInterest(double current_Sum, double rate, int year);
void countCurrentSum(double *sum, change_Values *amountList, int change_Number,
                     date_Values today);
void getDay(date_Values *today, int time);
int leap_Year(int year);
void capital_Function(int capital, deposit_Values *result,
                      double daily_Interest_Sum);
double monthly_Interest(double current_Sum, double rate, int year,
                        int days_In_Month);
void interest_Count(int capital, double *final_Amount, double interest,
                    double *total_Interest, double *year_Income);
void tax(deposit_Values *result, double year_Interest, double tax_Rate,
         double year_Income);
void interest_Calc(int capital, deposit_Values *result, double interest,
                   double *year_Income);

#endif  // SRC_S21_SMARTCALC_H_
