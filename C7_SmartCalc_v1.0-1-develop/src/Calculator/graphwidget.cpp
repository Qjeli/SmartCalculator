#include "graphwidget.h"

#include <math.h>

#include "ui_graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::GraphWidget)

{
  ui->setupUi(this);
}

void GraphWidget::slot(double Xmin, double Xmax, double Ymin, double Ymax,
                       char *str) {
  h = 0.01;

  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(Xmin, Xmax);
  ui->widget->yAxis->setRange(Ymin, Ymax);
  if (validation(str) == 1) {
    for (X = Xmin; X <= Xmax; X += h) {
      double Y = s21_calculator(str, X);
      if (Y <= Ymin * 2 || Y >= Ymax * 2) {
        Y = qQNaN();
      }
      x.push_back(X);
      y.push_back(Y);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

GraphWidget::~GraphWidget() { delete ui; }
