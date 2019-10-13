#ifndef DIALOGLINEARPOINTOPERATION_H
#define DIALOGLINEARPOINTOPERATION_H

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

class DialogLinearPointOperation : public QDialog
{

    Q_OBJECT

public:
    explicit DialogLinearPointOperation(QWidget *parent = nullptr);
    ~DialogLinearPointOperation();

public:
    QGridLayout *gridLayout;

    QDialogButtonBox *buttonBox;

    QLabel *labelSlope;
    QLabel *labelOffset;

    QLineEdit *lineEditSlope;
    QLineEdit *lineEditOffset;

    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalLinearPointOperation();
    void signalLinearPointOperationFinished(QImage &);

private slots:
    void emitSignalLinearPointOperation();

    void pointOperation(QImage *originImage);
};

#endif // DIALOGLINEARPOINTOPERATION_H
