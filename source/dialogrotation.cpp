#include "dialogrotation.h"

DialogRotation::DialogRotation(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalRotationEnd()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(Rotate(QImage *)));
}

DialogRotation::~DialogRotation()
{
}

void DialogRotation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogRotation"));
    this->setFixedSize(400, 112);

    labelAngle = new QLabel(this);
    labelAngle->setObjectName(QStringLiteral("labelAngle"));

    lineEditAngle = new QLineEdit(this);
    lineEditAngle->setObjectName(QStringLiteral("lineEditAngle"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addWidget(labelAngle, 0, 0);
    gridLayout->addWidget(lineEditAngle, 0, 1);
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    retranslate();

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogRotation::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogRotation", "Dialog", Q_NULLPTR));

    labelAngle->setText(QApplication::translate("DialogRotation", "设定旋转角度", Q_NULLPTR));
} // retranslate

void DialogRotation::emitSignalRotationEnd()
{
    emit signalRotationStart();
} // emitSignaRotationEnd

void DialogRotation::Rotate(QImage *originImage)
{
    double factor = M_PI / 180.0;
    // 取模
    int angle = (lineEditAngle->text().toInt()) % 360;
    double theta = angle * factor;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像旋转,"
                       << "旋转角度:" << angle << ";"
                       << "旋转弧度:" << theta;

    int width = originImage->width();
    int height = originImage->height();

    if (theta > M_PI && theta <= 2 * M_PI)
        theta = 2 * M_PI - theta;

    // 顺时针旋转 情况一
    // 判断旋转角度象限
    // 0 - π/2 => 第一象限, 用 + 表示
    // π/2 - π => 第二象限, 用 - 表示
    int symbol = qCos(theta) / qAbs(qCos(theta));

    int newWidth = height * qSin(theta) + symbol * width * qCos(theta);
    int newHeight = width * qSin(theta) + symbol * height * qCos(theta);

    QImage targetImage = QImage(newWidth, newHeight, QImage ::Format_RGB32);

    for (int i = 0; i < newWidth; i++)
        for (int j = 0; j < newHeight; j++)
            targetImage.setPixel(i, j, qRgb(255, 255, 255));

    // originImage 和 targetImage 原点坐标差值
    int deltaX = (-width * qCos(theta) + symbol * (width * qCos(theta))) / 2;
    int deltaY = (-height * qCos(theta) + symbol * (height * qCos(theta))) / 2 + width * qSin(theta);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // 在 originImage 坐标系中变换后的坐标
            int middleX = i * qCos(theta) - j * qSin(theta);
            int middleY = i * qSin(theta) + j * qCos(theta);

            QRgb rgb = QRgb(originImage->pixel(i, j));

            // 由于图片坐标和笛卡尔坐标原点不同, 所以这里变换坐标轴
            // targetImage 坐标系中的坐标
            int targetX = middleX + deltaY;
            int targetY = middleY + deltaX;

            if ((targetX >= 0) && (targetX < newWidth) && (targetY >= 0) && (targetY < newHeight))
                targetImage.setPixel(targetX, targetY, QRgb(rgb));
        }
    }

    emit signalRotationEnd((QImage &)targetImage);

} // Rotate
