#ifndef DIALOGSAMPLINGRATE_H
#define DIALOGSAMPLINGRATE_H

#include "mainwindow.h"
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

class DialogSamplingRate : public QDialog
{

    Q_OBJECT

public:
    explicit DialogSamplingRate(QWidget *parent = nullptr);
    ~DialogSamplingRate();

public:
    QDialogButtonBox *buttonBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalSetSamplingRate();
    void signalSetSamplingRateFinished(QImage &);

private slots:
    void emitSignalSetSamplingRate();
    void setSamplingRate(QImage *originImage);
};

#endif // DIALOGSAMPLINGRATE_H
