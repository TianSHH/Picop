#include "dialoggrayscalethreshold.h"

DialogGrayscaleThreshold::DialogGrayscaleThreshold(QWidget *parent) : QDialog(parent)
{
    setup();
}

DialogGrayscaleThreshold::~DialogGrayscaleThreshold()
{
}

void DialogGrayscaleThreshold::setup()
{
    slider = new QSlider(Qt::Horizontal);
    slider->setObjectName(QStringLiteral("slider"));
    slider->setMinimum(0);
    slider->setMaximum(255);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    gridLayout->addWidget(lineEdit, 0, 0);
    gridLayout->addWidget(slider, 0, 1);

    this->setLayout(gridLayout);
    this->resize(300, 50);
    this->setWindowTitle("设定灰度阀值");

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(setSliderValue()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(emitSignalThresholdChanged()));
}

void DialogGrayscaleThreshold::setLineEditValue()
{
    int pos = slider->value();
    QString str = QString("%1").arg(pos);
    lineEdit->setText(str);
}

void DialogGrayscaleThreshold::setSliderValue()
{
    slider->setValue(lineEdit->text().toInt());
} // setSliderValue

void DialogGrayscaleThreshold::emitSignalThresholdChanged()
{
    emit signalThresholdChanged(lineEdit->text().toInt());
} // emitSignalThresholdChanged
