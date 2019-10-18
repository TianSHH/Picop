#ifndef DIALOGLOGTRANS_H
#define DIALOGLOGTRANS_H

#include "qcustomplot.h"
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/qglobal.h>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

class DialogLogTransformation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogTransformation(QWidget *parent = nullptr);
    ~DialogLogTransformation();

public:
    QCustomPlot *customPlot;
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *doubleSpinBoxArgA;
    QDoubleSpinBox *doubleSpinBoxArgB;
    QDoubleSpinBox *doubleSpinBoxArgC;
    QLabel *labelArgA;
    QLabel *labelArgB;
    QLabel *labelArgC;
    QGridLayout *gridLayout;
    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();
    void paintFunctionImage(double a, double b, double c);

signals:
    void signalLogTransformationStart();
    void signalLogTransformationEnd(QImage &);

private slots:
    void on_doubleSpinBoxArgA_valueChanged(double arg);
    void on_doubleSpinBoxArgB_valueChanged(double arg);
    void on_doubleSpinBoxArgC_valueChanged(double arg);

    void emitSignalLogTransformationStart();

    void logTransformation(QImage *originImage);
};

#endif // !DIALOGLOGTRANS_H
