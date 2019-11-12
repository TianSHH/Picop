#ifndef DIALOGTRANSLATION_H
#define DIALOGTRANSLATION_H

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

class DialogTranslation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTranslation(QWidget *parent = nullptr);
    ~DialogTranslation();

public:
    QLabel *labelArgDeltaX;
    QLabel *labelArgDeltaY;

    QLineEdit *lineEditArgDeltaX;
    QLineEdit *lineEditArgDeltaY;

    QDialogButtonBox *buttonBox;

    QGridLayout *gridLayout;

    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalTranslationStart();
    void signalTranslationEnd(QImage &);

private slots:
    void emitSignalTranslationEnd();

    void Translation(QImage *originImage);
};

#endif // DIALOGTRANSLATION_H
