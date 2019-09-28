#ifndef DIALOGSAMPLINGRATE_H
#define DIALOGSAMPLINGRATE_H

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

public:
    void setup();
    void retranslate();

signals:
    void signalSetSamplingRate(const int &);

private slots:
    void emitSignalSetSamplingRate();
};

#endif // DIALOGSAMPLINGRATE_H
