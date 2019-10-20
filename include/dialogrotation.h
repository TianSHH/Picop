#ifndef DIALOGROTATION_H
#define DIALOAROTATION_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/QtMath>
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

class DialogRotation : public QDialog
{

    Q_OBJECT

public:
    DialogRotation(QWidget *parent = nullptr);
    ~DialogRotation();

public:
    QLabel *labelAngle;

    QLineEdit *lineEditAngle;

    QDialogButtonBox *buttonBox;

    QGridLayout *gridLayout;

    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalRotationStart();
    void signalRotationEnd(QImage &);

private slots:
    void emitSignalRotationEnd();

    void Rotate(QImage *originImage);
};
#endif // !DIALOGROTATION_H
