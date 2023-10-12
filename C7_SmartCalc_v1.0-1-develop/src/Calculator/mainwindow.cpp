#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  graph = new GraphWidget;
  connect(this, &MainWindow::signal, graph, &GraphWidget::slot);

  ui->lineEdit->setPlaceholderText("0.00");
  ui->lineEdit->setFocus();
  ui->radioButtonAnnuitet->setChecked(true);

  QDate date = QDate::currentDate();
  ui->dateEditAdd->setDate(date);
  QString formattedTime = date.toString("dd.MM.yyyy");
  ui->textEditDateBegin->setText(formattedTime);

  connect(ui->PushButton0, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton1, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton2, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton3, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton4, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton5, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton6, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton7, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton8, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButton9, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonBracOpen, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->PushButtonBracClose, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->PushButtonX, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonCos, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAcos, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonSin, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAsin, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMod, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonTan, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAtan, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonExp, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonLn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonLog, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonSqrt, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonDiv, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMult, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonMinus, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonPlus, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonEqual, SIGNAL(clicked()), this,
          SLOT(ButtonEqualPressed()));
  connect(ui->PushButtonDot, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->PushButtonAC, SIGNAL(clicked()), this, SLOT(ButtonACPressed()));
  connect(ui->PushButtonDel, SIGNAL(clicked()), this, SLOT(ButtonDelPressed()));
  connect(ui->PushButtonGraph, SIGNAL(clicked()), this,
          SLOT(GraphingButtonPressed()));
  connect(ui->pushButtonCreditCalc, SIGNAL(clicked()), this,
          SLOT(CreditCalc()));
  connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(ButtonAddPressed()));
  connect(ui->pushButtonDepositCalc, SIGNAL(clicked()), this,
          SLOT(DepositCalc()));
  connect(ui->pushButtonDelete, SIGNAL(clicked()), this,
          SLOT(ButtonDeletePressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString numbers = "0123456789.- ";
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->setText(ui->lineEdit->text() += button_text);
    if ((button_text == "acos") || (button_text == "asin") ||
        (button_text == "atan") || (button_text == "cos") ||
        (button_text == "sin") || (button_text == "tan") ||
        (button_text == "log") || (button_text == "ln") ||
        (button_text == "sqrt"))
      ui->lineEdit->setText(ui->lineEdit->text() += "(");
  } else if (ui->lineEdit_X->hasFocus() &&
             numbers.contains(button_text, Qt::CaseInsensitive)) {
    ui->lineEdit_X->setText(ui->lineEdit_X->text() += button_text);
  }
}

void MainWindow::GraphingButtonPressed() {
  graph->show();
  double Xmin = ui->lineEditXmin->text().toDouble();
  double Xmax = ui->lineEditXmax->text().toDouble();
  double Ymin = ui->lineEditYmin->text().toDouble();
  double Ymax = ui->lineEditYmax->text().toDouble();
  QString display_value = ui->lineEdit->text();
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  emit signal(Xmin, Xmax, Ymin, Ymax, str);
}

void MainWindow::ButtonEqualPressed() {
  QString display_value = "";
  display_value = ui->lineEdit->text();
  display_value.remove(" ");
  QByteArray ds = display_value.toLocal8Bit();
  char *str = ds.data();
  QString x_value = ui->lineEdit_X->text();
  double x = x_value.toDouble();
  if (validation(str) == 1) {
    double result = 0;
    result = s21_calculator(str, x);
    QString str_res = QString::number(result, 'g', 16);
    if (isnan(result) || isinf(result)) {
      ui->lineEdit->setText("ERROR! INCORRECT EXPRESSION");
    } else {
      ui->lineEdit->setText(str_res);
    }
  } else {
    ui->lineEdit->setText("ERROR! INCORRECT EXPRESSION");
  }
}

void MainWindow::ButtonDelPressed() {
  QString tmp = "";
  if (ui->lineEdit->hasFocus()) {
    tmp = ui->lineEdit->text();
    tmp.chop(1);
    ui->lineEdit->setText(tmp);
  } else if (ui->lineEdit_X->hasFocus()) {
    tmp = ui->lineEdit_X->text();
    tmp.chop(1);
    ui->lineEdit_X->setText(tmp);
  }
}

void MainWindow::ButtonACPressed() {
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->clear();
  } else if (ui->lineEdit_X->hasFocus()) {
    ui->lineEdit_X->clear();
  }
}

void MainWindow::CreditCalc() {
  double amount = 0.0;
  amount = ui->lineEditLoanSum->text().toDouble();
  int time = 0;
  time = ui->lineEditTerm->text().toInt();
  double rate = 0;
  rate = ui->lineEditRate->text().toDouble();
  int type = 0;
  if (ui->radioButtonAnnuitet->isChecked() == true) {
    type = annuity;
  }
  if (ui->radioButtonDifferent->isChecked() == true) {
    type = differ;
  }
  if (ui->comboBoxTerm->currentText() == "лет") {
    time *= 12;
  }
  credit_Values creditStruct = {0, 0, 0, 0, 0};
  creditStruct = credit_calc(amount, time, rate / 100, type);
  if (type == differ) {
    ui->labelPayment->setText(
        QString::number(creditStruct.monthlyPaymentFrst, 'f', 2) + " ... " +
        QString::number(creditStruct.monthlyPaymentLst, 'f', 2) + " руб.");
  }
  if (type == annuity) {
    ui->labelPayment->setText(
        QString::number(creditStruct.monthly_Payment, 'f', 2) + " руб.");
  }
  ui->labelOverpay->setText(QString::number(creditStruct.over_Payment, 'f', 2) +
                            " руб.");
  ui->labelTotal->setText(QString::number(creditStruct.total_Payment, 'f', 2) +
                          " руб.");
}

void MainWindow::ButtonAddPressed() {
  QString AddDate = "";
  AddDate = ui->dateEditAdd->text();
  QString AddSum = "";
  AddSum = ui->lineEditDepositAdditional->text();
  QString AddAll = "";
  AddAll = AddDate + '\t' + AddSum + '\t';
  ui->textEditAdd->append(AddAll);
}

void MainWindow::DepositCalc() {
  QByteArray ds = ui->textEditAdd->toPlainText().toLocal8Bit();
  char *add_list = ds.data();
  deposit_Values depositStruct = {0, 0, 0};
  double amount = 0.0;
  amount = ui->lineEditDepositSum->text().toDouble();
  int time = 0;
  time = ui->lineEditDepositTerm->text().toInt();
  double rate = 0;
  rate = ui->lineEditDepositRate->text().toDouble();
  int paymentPeriod = 0;
  int capital = without_Capital;
  if (ui->comboBoxDepositTerm->currentText() == "ежедневно")
    paymentPeriod = daily;
  else if (ui->comboBoxDepositTerm->currentText() == "раз в месяц")
    paymentPeriod = monthly;
  if (ui->checkBoxDeposit->isChecked() == true) capital = with_Capital;
  depositStruct = deposit_calc(amount, time, rate / 100, 0.13, paymentPeriod,
                               capital, add_list);
  ui->labelInterest->setText(
      QString::number(depositStruct.total_Interest, 'f', 2) + " руб.");
  ui->labelTax->setText(QString::number(depositStruct.tax_Amount, 'f', 2) +
                        " руб.");
  ui->labelTotalDep->setText(
      QString::number(depositStruct.final_Amount, 'f', 2) + " руб.");
}

void MainWindow::ButtonDeletePressed() { ui->textEditAdd->clear(); }
