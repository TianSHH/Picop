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

class DialogNolinearPointOperation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNolinearPointOperation(QWidget *parent = nullptr);
    ~DialogNolinearPointOperation();

public:
    QGridLayout *gridLayout;

    QLabel *labelVar;
    QLineEdit *lineEditVar;

    QDialogButtonBox *buttonBox;

    QMainWindow *ptr = (QMainWindow *)parentWidget();

    QString transformType = "null";

    int rM = 0;
    int gM = 0;
    int bM = 0;

public:
    void setupNolinearGrayscaleTransform();
    void setupSinTransform();
    void setupTanTransform();

signals:
    void signalNoLinearPointOperation();
    void signalNoLinearPointOperationFinshed();

private slots:
    void emitSignalNolinearPointOperation();

    void transformTypeSwitch(QString transformType, QImage *originImage);

public:
    void nolinearGrayscaleTransform(QImage *originImage);
    void SinTransform(QImage *originImage);
    void TanTransform(QImage *originImage);
};

#endif // DIALOGNOLINEARPOINTOPERATION_H
