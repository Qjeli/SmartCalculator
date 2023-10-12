#include "s21_smartcalc.h"

deposit_Values deposit_calc(double amount, int time, double rate,
                            double taxRate, int payment, int capital,
                            char *change) {
  deposit_Values result = {0};
  change_Values amountList[100] = {0};
  date_Values today = {0};
  date_Values yesterday = {0};
  int changeNumber = 0;
  result.final_Amount = amount;
  double interest = 0;
  changeNumber = change_Parcer(change, amountList);
  getDay(&today, 0);
  int currentYear = today.year;
  double yearInterest = 0;
  double yearIncome = 0;
  for (int i = 1; i <= time; i++) {
    getDay(&today, i);
    if (today.year > currentYear) {
      yearInterest += (yearIncome - 75000);
      yearIncome = 0;
    }
    getDay(&yesterday, i - 1);
    countCurrentSum(&result.final_Amount, amountList, changeNumber, yesterday);
    if (payment == daily) {
      interest = dailyInterest(result.final_Amount, rate, today.year);
      interest_Calc(capital, &result, interest, &yearIncome);
    } else if (payment == monthly && today.day == 1) {
      interest = monthly_Interest(result.final_Amount, rate, today.year,
                                  yesterday.day);
      interest_Calc(capital, &result, interest, &yearIncome);
    }

    currentYear = today.year;
  }
  tax(&result, yearInterest, taxRate, yearIncome);
  return result;
}

void interest_Calc(int capital, deposit_Values *result, double interest,
                   double *year_Income) {
  capital_Function(capital, result, interest);
  result->total_Interest += interest;
  *year_Income += interest;
}

void tax(deposit_Values *result, double year_Interest, double tax_Rate,
         double year_Income) {
  result->tax_Amount += year_Interest * tax_Rate;
  if (year_Income > 75000) {
    result->tax_Amount += (year_Income - 75000) * tax_Rate;
  }
  if (result->tax_Amount < 0) {
    result->tax_Amount = 0;
  }
}

int change_Parcer(char *change, change_Values *amount_List) {
  int count = 0;
  while (*change) {
    amount_List[count].day = strtol(change, &change, 10);
    change++;
    amount_List[count].month = strtol(change, &change, 10);
    change++;
    amount_List[count].year = strtol(change, &change, 10);
    change++;
    amount_List[count].sum = strtod(change, &change);
    count++;
  }
  return count;
}

double dailyInterest(double current_Sum, double rate, int year) {
  double result = 0.0;
  result = current_Sum * rate / (365 + leap_Year(year));
  return result;
}

double monthly_Interest(double current_Sum, double rate, int year,
                        int days_In_Month) {
  double result = 0.0;
  result = (current_Sum * rate / (365 + leap_Year(year))) * days_In_Month;
  return result;
}

void countCurrentSum(double *sum, change_Values *amountList, int change_Number,
                     date_Values today) {
  for (int i = 0; i < change_Number; i++) {
    if (today.day == amountList[i].day &&
        today.month + 1 == amountList[i].month &&
        today.year + 1900 == amountList[i].year) {
      *sum += amountList[i].sum;
    }
  }
}

void capital_Function(int capital, deposit_Values *result,
                      double daily_Interest_Sum) {
  if (capital == with_Capital) {
    result->final_Amount += daily_Interest_Sum;
  }
}

void getDay(date_Values *today, int term) {
  const time_t timer = time(NULL);
  struct tm *today_str = localtime(&timer);
  time_t next = mktime(today_str);
  today_str->tm_mday += term;
  next = mktime(today_str);
  today_str = localtime(&next);
  today->day = today_str->tm_mday;
  today->month = today_str->tm_mon;
  today->year = today_str->tm_year;
}

int leap_Year(int year) {
  int res = 0;
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) res = 1;
  return res;
}
