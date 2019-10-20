#include "dialogscaling.h"

DialogScaling::DialogScaling(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalScalingEnd()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(Scaling(QImage *)));
}

DialogScaling::~DialogScaling()
{
}

void DialogScaling::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogScaling"));
    this->setFixedSize(400, 112);

    labelWidthScalingFactor = new QLabel(this);
    labelWidthScalingFactor->setObjectName(QStringLiteral("labelWidthScalingFactor"));
    labelHeightScalingFactor = new QLabel(this);
    labelHeightScalingFactor->setObjectName(QStringLiteral("labelHeightScalingFactor"));

    // 将限制器 notation 方式手动设置为 "StandardNotation"
    // 否则会构建失效
    // ? 限制器上界并不是 10.0
    doubleValidator = new QDoubleValidator(0.00, 10.00, 2, this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    lineEditWidthScalingFactor = new QLineEdit(this);
    lineEditWidthScalingFactor->setObjectName(QStringLiteral("lineEditWidthScalingFactor"));
    lineEditWidthScalingFactor->setValidator(doubleValidator);

    lineEditHeightScalingFactor = new QLineEdit(this);
    lineEditHeightScalingFactor->setObjectName(QStringLiteral("lineEditHeightScalingFactor"));
    lineEditHeightScalingFactor->setValidator(doubleValidator);

    radioButton1 = new QRadioButton(this);
    radioButton1->setObjectName(QStringLiteral("radioButton1"));
    radioButton1->setChecked(true);

    radioButton2 = new QRadioButton(this);
    radioButton2->setObjectName(QStringLiteral("radioButton2"));
    radioButton2->setChecked(false);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addWidget(labelWidthScalingFactor, 0, 0);
    gridLayout->addWidget(labelHeightScalingFactor, 1, 0);
    gridLayout->addWidget(lineEditWidthScalingFactor, 0, 1);
    gridLayout->addWidget(lineEditHeightScalingFactor, 1, 1);
    gridLayout->addWidget(radioButton1, 2, 0);
    gridLayout->addWidget(radioButton2, 2, 1);
    gridLayout->addWidget(buttonBox, 3, 0, 1, 2);

    retranslate();

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogScaling::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogScaling", "Dialog", Q_NULLPTR));

    labelWidthScalingFactor->setText(QApplication::translate("DialogScaling", "设定水平方向放大倍数", Q_NULLPTR));
    lineEditWidthScalingFactor->setText("1.0");
    labelHeightScalingFactor->setText(QApplication::translate("DialogScaling", "设定竖直方向放大倍数", Q_NULLPTR));
    lineEditHeightScalingFactor->setText("1.0");

    radioButton1->setText(QApplication::translate("MainWindow", "最近邻插值", Q_NULLPTR));
    radioButton2->setText(QApplication::translate("MainWindow", "双线性插值", Q_NULLPTR));
} // retranslate

void DialogScaling::emitSignalScalingEnd()
{
    emit signalScalingStart();
} // emitSignalScalingEnd

void DialogScaling::Scaling(QImage *originImage)
{
    if (radioButton1->isChecked())
        scalingNNI(originImage);
    else if (radioButton2->isChecked())
        scalingBI(originImage);
} // Scaling

void DialogScaling::scalingNNI(QImage *originImage)
{
    getInfo(originImage);

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像平移,"
                       << "最邻近插值法,"
                       << "水平方向放大倍数:" << factorX << ";"
                       << "竖直方向放大倍数:" << factorY;

    QImage targetImage = QImage(targetWidth, targetHeight, QImage::Format_RGB32);

    // 最邻近插值法
    for (int targetX = 0; targetX < targetWidth; targetX++)
        for (int targetY = 0; targetY < targetHeight; targetY++)
        {
            int originX = (int)(targetX / factorX + 0.5);

            if (originX >= originWidth)
                originX--;

            int originY = (int)(targetY / factorY + 0.5);

            if (originY >= originHeight)
                originY--;

            QRgb rgb = QRgb(originImage->pixel(originX, originY));

            targetImage.setPixel(targetX, targetY, QRgb(rgb));
        }

    emit signalScalingEnd((QImage &)targetImage);
} // scalingNNI

void DialogScaling::scalingBI(QImage *originImage)
{
    getInfo(originImage);

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像平移,"
                       << "双线性插值法,"
                       << "水平方向放大倍数:" << factorX << ";"
                       << "竖直方向放大倍数:" << factorY;

    QImage targetImage = QImage(targetWidth, targetHeight, QImage::Format_RGB32);

    // 双线性插值
    for (int targetX = 0; targetX < targetWidth; targetX++)
        for (int targetY = 0; targetY < targetHeight; targetY++)
        {
            double originX = targetX / factorX;
            double originY = targetY / factorY;

            QPoint p1((int)originX, (int)originY);

            double u = originX - p1.x();
            double v = originY - p1.y();

            int red = 255;
            int green = 255;
            int blue = 255;

            /*******************************************
             *   
             * p1(x,y)----------------(x+1,y)-----
             *     |         ^           |
             *     |         |           |
             *     |         v           |     
             *     |         |           |
             *     |         v           |
             *     |<---u--->* case 4    |    * case 2
             *     |                     |
             *     |                     |
             *     |                     |
             *   (x,y+1)-------------(x+1,y+1)----
             *     |                     |
             *     |         * case 3    |    * case 1
             *     |                     |
             *   
             *   ****************************************/

            // case 1
            if ((originX >= originWidth - 1) && (originY >= originHeight - 1))
            {
                QColor color = QColor(originImage->pixel(p1.x(), p1.y()));

                red = color.red();
                green = color.green();
                blue = color.blue();
            }
            // case 2
            else if (originX >= originWidth - 1)
            {
                QColor color1 = QColor(originImage->pixel(p1.x(), p1.y()));
                QColor color2 = QColor(originImage->pixel(p1.x(), p1.y() + 1));

                red = color1.red() * (1 - v) + color2.red() * v;
                green = color1.green() * (1 - v) + color2.green() * v;
                blue = color1.blue() * (1 - v) + color2.blue() * v;
            }
            // case3
            else if (originY >= originHeight - 1)
            {
                QColor color1 = QColor(originImage->pixel(p1.x(), p1.y()));
                QColor color2 = QColor(originImage->pixel(p1.x() + 1, p1.y()));

                red = color1.red() * (1 - v) + color2.red() * v;
                green = color1.green() * (1 - v) + color2.green() * v;
                blue = color1.blue() * (1 - v) + color2.blue() * v;
            }
            // case 4
            else
            {
                QColor color1 = QColor(originImage->pixel(p1.x(), p1.y()));
                QColor color2 = QColor(originImage->pixel(p1.x() + 1, p1.y()));
                QColor color3 = QColor(originImage->pixel(p1.x(), p1.y() + 1));
                QColor color4 = QColor(originImage->pixel(p1.x() + 1, p1.y() + 1));

                red = color1.red() * (1 - u) + color2.red() * u;
                green = color1.green() * (1 - u) + color2.green() * u;
                blue = color1.blue() * (1 - u) + color2.blue() * u;

                int red1 = color3.red() * (1 - u) + color4.red() * u;
                int green1 = color3.green() * (1 - u) + color4.green() * u;
                int blue1 = color3.blue() * (1 - u) + color4.blue() * u;

                red = red * (1 - v) + red1 * v;
                green = green * (1 - v) + green1 * v;
                blue = blue * (1 - v) + blue1 * v;
            }

            targetImage.setPixel(targetX, targetY, qRgb(red, green, blue));
        }

    emit signalScalingEnd((QImage &)(targetImage));
} // scalingBI

void DialogScaling::getInfo(QImage *originImage)
{
    factorX = lineEditWidthScalingFactor->text().toDouble();
    factorY = lineEditHeightScalingFactor->text().toDouble();

    originWidth = originImage->width();
    originHeight = originImage->height();

    targetWidth = originWidth * factorX;
    targetHeight = originHeight * factorY;
} // getInfo
