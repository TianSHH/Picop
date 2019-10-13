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
#include <QtWidgets/QMainWindow>

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
    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();

signals:
    void signalSetQuantifyLevel();
    void signalSetQuantifyLevelFinished(QImage &);

private slots:
    void emitSignalSetQuantifyLevel();

    void setQuantifyLevel(QImage *originImage);
};

#endif // DIALOGQUANTIFYLEVEL_H
