#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

#ifdef __cplusplus
extern "C" {
#endif
#include "s21_smartcalc.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget {
  Q_OBJECT

 public:
  explicit GraphWidget(QWidget *parent = nullptr);
  ~GraphWidget();

 private:
  Ui::GraphWidget *ui;
  double X, h;
  QVector<double> x, y;

 public slots:
  void slot(double Xmin, double Xmax, double Ymin, double Ymax, char *str);
};

#endif  // GRAPHWIDGET_H
