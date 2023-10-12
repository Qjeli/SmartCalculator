#include "s21_smartcalc.h"

credit_Values credit_calc(double amount, int time, double rate, int type) {
  credit_Values creditResult = {0};
  if (type == annuity) {
    rate /= 12;
    creditResult.monthly_Payment =
        amount * ((rate * pow((1 + rate), time)) / (pow((1 + rate), time) - 1));
    creditResult.over_Payment = creditResult.monthly_Payment * time - amount;
    creditResult.total_Payment = amount + creditResult.over_Payment;
  }
  if (type == differ) {
    double monthPrincipalPay = 0;
    monthPrincipalPay = amount / time;
    for (int i = 0; i < time; i++) {
      creditResult.monthly_Payment =
          (amount - (monthPrincipalPay * i)) * rate / 12 + monthPrincipalPay;
      creditResult.total_Payment += creditResult.monthly_Payment;
    }
    creditResult.monthlyPaymentFrst =
        (amount - (monthPrincipalPay * 0)) * rate / 12 + monthPrincipalPay;
    creditResult.monthlyPaymentLst =
        (amount - (monthPrincipalPay * (time - 1))) * rate / 12 +
        monthPrincipalPay;
    creditResult.over_Payment = creditResult.total_Payment - amount;
  }
  if (time <= 0 || rate <= 0) {
    memset(&creditResult, '0', sizeof(creditResult));
  }
  return creditResult;
}