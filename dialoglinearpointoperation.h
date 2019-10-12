#ifndef DIALOGLINEARPOINTOPERATION
#define DIALOGLINEARPOINTOPERATION

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

class DialogLinearPointOperation : public QDialog
{
public:
    explicit DialogLinearPointOperation(QWidget *parent = nullptr);
    ~DialogLinearPointOperation();

public:
    QGridLayout *gridLayout;

    QDialogButtonBox *buttonBox;

    QLineEdit *lineEditSlope;
    QLineEdit *lineEditOffset;

    QMainWindow *ptr = (QMainWindow *) parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalLinearPointOperation();
    void signalLinearPointOperationFinished(QImage &);

private slots:
    void emitSignalPointLinearOperation();

    void pointOperation(QImage *originImage);
};

#endif // DIALOGLINEARPOINTOPERATION
