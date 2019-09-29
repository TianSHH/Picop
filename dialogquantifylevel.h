#ifndef DIALOGQUANTIFYLEVEL_H
#define DIALOGQUANTIFYLEVEL_H

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

class DialogQuantifyLevel : public QDialog
{

    Q_OBJECT

public:
    explicit DialogQuantifyLevel(QWidget *parent = nullptr);
    ~DialogQuantifyLevel();

public:
    QDialogButtonBox *buttonBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;

public:
    void setup();
    void retranslate();

signals:
    void signalSetQuantifyLevel(const int &);

private slots:
    void emitSignalSetQuantifyLevel();
};

#endif // DIALOGQUANTIFYLEVEL_H


    // qDebug("[Debug] %s: %s %d", qPrintable(QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz")), "设定灰度阀值", threshold);
