#include "dialogtranslation.h"

DialogTranslation::DialogTranslation(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalSetSamplingRate()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(setSamplingRate(QImage *)));
}

DialogTranslation::~DialogTranslation()
{
}

void DialogTranslation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogTranslation"));
    this->setFixedSize(400, 112);

    labelArgDeltaX = new QLabel(this);
    labelArgDeltaX->setObjectName(QStringLiteral("labelArgDeltaX"));
    labelArgDeltaY = new QLabel(this);
    labelArgDeltaY->setObjectName(QStringLiteral("labelArgDeltaY"));

    lineEditArgDeltaX = new QLineEdit(this);
    lineEditArgDeltaX->setObjectName(QStringLiteral("lineEditArgDeltaX"));
    lineEditArgDeltaY = new QLineEdit(this);
    lineEditArgDeltaY->setObjectName(QStringLiteral("lineEditArgDeltaY"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    gridLayout->addWidget(labelArgDeltaX, 0, 0);
    gridLayout->addWidget(labelArgDeltaY, 1, 0);
    gridLayout->addWidget(lineEditArgDeltaX, 0, 1);
    gridLayout->addWidget(lineEditArgDeltaY, 1, 1);
    gridLayout->addWidget(buttonBox, 2, 0, 1, 2);

    retranslate();

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogTranslation::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogTranslation", "Dialog", Q_NULLPTR));
    labelArgDeltaX->setText(QApplication::translate("DialogTranslation", "设定水平偏移量", Q_NULLPTR));
    labelArgDeltaY->setText(QApplication::translate("DialogTranslation", "设定竖直偏移量", Q_NULLPTR));
} // retranslate

void DialogTranslation::emitSignalSetSamplingRate()
{
    int rate = lineEdit->text().toInt();

    if (lineEdit->text().isEmpty())
        return;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定采样率" << rate;
    emit signalSetSamplingRate();
} // emitSignalSetSamplingRate

void DialogTranslation::setSamplingRate(QImage *originImage)
{
    int rate = lineEdit->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改采样率" << rate;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i += rate)
        for (int j = 0; j < height; j += rate)
        {
            QColor color = QColor(originImage->pixel(i, j));
            int r = color.red();
            int g = color.green();
            int b = color.blue();

            originImage->setPixel(i + 1, j + 1, qRgb(r, g, b));

            for (int p = 0; p < rate && i + p < height; p++)
                for (int q = 0; q < rate && j + q < width; q++)
                    originImage->setPixel(i + p, j + q, qRgb(r, g, b));
        }

    emit signalSetSamplingRateFinished((QImage &)(*originImage));
} // setSamplingRate
