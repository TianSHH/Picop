#ifndef DIALOGPOWERTRANSFORMATION_H
#define DIALOGPOWERTRANSFORMATION_H

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

class DialogPowerTransformation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPowerTransformation(QWidget *parent = nullptr);
    ~DialogPowerTransformation();

public:
    QCustomPlot *customPlot;
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *doubleSpinBoxArgC;
    QDoubleSpinBox *doubleSpinBoxArgR;
    QDoubleSpinBox *doubleSpinBoxArgB;
    QLabel *labelArgC;
    QLabel *labelArgR;
    QLabel *labelArgB;
    QGridLayout *gridLayout;
    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();
    void paintFunctionImage(double c, double r, double b);

signals:
    void signalPowerTransformationStart();
    void signalPowerTransformationEnd(QImage &);

private slots:
    void on_doubleSpinBoxArgC_valueChanged(double arg);
    void on_doubleSpinBoxArgR_valueChanged(double arg);
    void on_doubleSpinBoxArgB_valueChanged(double arg);

    void emitSignalPowerTransformationStart();
    void powerTransformation(QImage *originImage);
};

#endif // DIALOGPOWERTRANSFORMATION_H
