#ifndef DIALOGGRAYSCALETHRESHOLD_H
#define DIALOGGRAYSCALETHRESHOLD_H

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

class DialogGrayscaleThreshold : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGrayscaleThreshold(QWidget *parent = nullptr);
    ~DialogGrayscaleThreshold();

public:
    QLineEdit *lineEdit;
    QGridLayout *gridLayout;
    QSlider *slider;

public:
    void setup();

signals:
    void signalThresholdChanged(const int &);

private slots:
    void setLineEditValue();
    void setSliderValue();

    void emitSignalThresholdChanged();
};

#endif // DIALOGGRAYSCALETHRESHOLD_H
