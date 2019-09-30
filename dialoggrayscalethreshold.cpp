#include "dialoggrayscalethreshold.h"

DialogGrayscaleThreshold::DialogGrayscaleThreshold(QWidget *parent) : QDialog(parent)
{
    setup();
    setAttribute(Qt::WA_DeleteOnClose);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(emitSignalSetGrayscaleThreshold()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(setGrayscaleThreshold(QImage *)), Qt::UniqueConnection);
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
} // setup

void DialogGrayscaleThreshold::setLineEditValue()
{
    int pos = slider->value();
    QString str = QString("%1").arg(pos);
    lineEdit->setText(str);
} // setLineEditValue

void DialogGrayscaleThreshold::setSliderValue()
{
    slider->setValue(lineEdit->text().toInt());
} // setSliderValue

void DialogGrayscaleThreshold::emitSignalSetGrayscaleThreshold()
{
    emit signalSetGrayscaleThreshold();
} // emitSignalThresholdChanged

void DialogGrayscaleThreshold::setGrayscaleThreshold(QImage *originImage)
{
    int threshold = lineEdit->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改灰度阀值" << threshold;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = QColor(originImage->pixel(i, j));
            int gray = color.red();

            if (gray < threshold)
                originImage->setPixel(i, j, qRgb(0, 0, 0));
            else
                originImage->setPixel(i, j, qRgb(255, 255, 255));
        }
    }
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像二值化";

    emit signalSetGrayscaleThresholdFinished((QImage &)(*originImage));
} // setGrayscaleThreshold
