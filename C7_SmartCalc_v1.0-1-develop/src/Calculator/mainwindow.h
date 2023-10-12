#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graphwidget.h>

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GraphWidget *graph;

 signals:
  void signal(double Xmin, double Xmax, double Ymin, double Ymax, char *str);

 private slots:
  void ButtonPressed();
  void ButtonDelPressed();
  void ButtonACPressed();
  void GraphingButtonPressed();
  void ButtonEqualPressed();
  void CreditCalc();
  void DepositCalc();
  void ButtonAddPressed();
  void ButtonDeletePressed();
};

#endif  // MAINWINDOW_H
