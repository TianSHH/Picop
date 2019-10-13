#ifndef DIALOGNOLINEARPOINTOPERATION_H
#define DIALOGNOLINEARPOINTOPERATION_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

class DialogNolinearpointoperation:public QDialog
{
    Q_OBJECT

public:
    explicit DialogNolinearpointoperation(QWidget *parent = nullptr);
    ~DialogNolinearpointoperation();


};

#endif // DIALOGNOLINEARPOINTOPERATION_H
