#include "dialogtranslation.h"

DialogTranslation::DialogTranslation(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalTranslationEnd()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(Translation(QImage *)));
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

void DialogTranslation::emitSignalTranslationEnd()
{
    emit signalTranslationStart();
} // emitSignalTranslationEnd

void DialogTranslation::Translation(QImage *originImage)
{
    int deltaX = lineEditArgDeltaX->text().toInt();
    int deltaY = lineEditArgDeltaY->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像平移,"
                       << "水平偏移量:" << deltaX << ";"
                       << "竖直偏移量:" << deltaY;

    int width = originImage->width();
    int height = originImage->height();

    QImage targetImage = QImage(width, height, QImage::Format_RGB32);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            targetImage.setPixel(i, j, qRgb(255, 255, 255));

    // 开始平移的初始坐标
    int i = (width - deltaX) % width;
    int j = (height - deltaY) % height;

    // 步长, 根据偏移量符号判断坐标 ++ 还是 --
    int stepX = deltaX / qAbs(deltaX);
    int stepY = deltaY / qAbs(deltaY);

    // deltaX 有正有负, 用这种方式规避正负问题
    int translationNumX = width - stepX * deltaX;
    int translationNumY = height - stepY * deltaY;

    for (int originX = i, countX = 0; countX < translationNumX; originX -= stepX, countX++)
    { // 由于无法确定 originX >= 0 还是 originX < width, 所以采用 countX 进行计数
        // 若 countX <= translationX 则会因多计算一次而出现黑边
        for (int originY = j, countY = 0; countY < translationNumY; originY -= stepY, countY++)
        {
            QRgb rgb = QRgb(originImage->pixel(originX, originY));

            // 开始平移时的目标坐标
            int targetX = originX + deltaX;
            int targetY = originY + deltaY;

            if ((targetX < width) && (targetY < height))
                targetImage.setPixel(targetX, targetY, QRgb(rgb));
        }
    }

    emit signalTranslationEnd((QImage &)(targetImage));
} // Translation
