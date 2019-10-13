#include "dialognolinearpointoperation.h"

DialogNolinearPointOperation::DialogNolinearPointOperation(QWidget *parent) : QDialog(parent)
{
    setup();
    setAttribute(Qt::WA_DeleteOnClose);

    // 触发的槽函数参数要和接收的信号所携带的参数一样
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalNolinearPointOperation()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(transformTypeSwitch(QImage *)));
}

DialogNolinearPointOperation::~DialogNolinearPointOperation()
{
}

void DialogNolinearPointOperation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogNolinearPointOperation"));
    this->setFixedSize(300, 112);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    labelVar = new QLabel(this);
    labelVar->setObjectName(QStringLiteral("labelVar"));

    lineEditVar = new QLineEdit(this);
    lineEditVar->setObjectName(QStringLiteral("lineEditVar"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal); // 设置 buttonBox 内部的布局
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(labelVar, 0, 0);
    gridLayout->addWidget(lineEditVar, 0, 1);
    gridLayout->addWidget(buttonBox, 1, 0, 1, 2);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);

    this->setWindowTitle("设定非线性灰度变换函数参数");
    labelVar->setText(QApplication::translate("设定非线性灰度变换函数参数", "C", Q_NULLPTR));
} // setup

void DialogNolinearPointOperation::setTransformMode(QString mode)
{
    transformType = mode;
} // grayscaleTransform

void DialogNolinearPointOperation::transformTypeSwitch(QImage *originImage)
{
    if (transformType == "grayscaleTransform")
        grayscaleTransform(originImage);
    else if (transformType == "sinTransform")
        sinTransform(originImage);
    else if (transformType == "tanTransform")
        tanTransform(originImage);
} // transformTypeSwitch

void DialogNolinearPointOperation::emitSignalNolinearPointOperation()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定非线性点运算参数";

    emit signalNoLinearPointOperation();
}

void DialogNolinearPointOperation::grayscaleTransform(QImage *originImage)
{
    double arg = lineEditVar->text().toDouble();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行非线性灰度变换"
                       << "参数:" << arg;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));
            rM = rM > _color.red() ? rM : _color.red();
            gM = gM > _color.green() ? gM : _color.green();
            bM = bM > _color.blue() ? bM : _color.blue();
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));

            double result = (_color.red() + arg * _color.red() * (rM - _color.red())) / rM;
            double r = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (_color.green() + arg * _color.green() * (gM - _color.green())) / gM;
            double g = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (_color.blue() + arg * _color.blue() * (bM - _color.blue())) / bM;
            double b = result > 255 ? 255 : (result < 0 ? 0 : result);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalNoLinearPointOperationFinshed((QImage &)(*originImage));
} // nolinearGrayscaleTransform

void DialogNolinearPointOperation::sinTransform(QImage *originImage)
{
    double arg = lineEditVar->text().toDouble();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行非线性正弦变换"
                       << "参数:" << arg;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));
            rM = rM > _color.red() ? rM : _color.red();
            gM = gM > _color.green() ? gM : _color.green();
            bM = bM > _color.blue() ? bM : _color.blue();
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));

            double result = (rM / 2) * (1 + (1 / (sin((M_PI * arg) / 2))) * sin(arg * M_PI * (_color.red() / rM - 1 / 2)));
            double r = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (gM / 2) * (1 + (1 / (sin((M_PI * arg) / 2))) * sin(arg * M_PI * (_color.green() / gM - 1 / 2)));
            double g = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (bM / 2) * (1 + (1 / (sin((M_PI * arg) / 2))) * sin(arg * M_PI * (_color.blue() / bM - 1 / 2)));
            double b = result > 255 ? 255 : (result < 0 ? 0 : result);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalNoLinearPointOperationFinshed((QImage &)(*originImage));
} // sinTransform

void DialogNolinearPointOperation::tanTransform(QImage *originImage)
{
    double arg = lineEditVar->text().toDouble();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行非线性正切变换"
                       << "参数:" << arg;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));
            rM = rM > _color.red() ? rM : _color.red();
            gM = gM > _color.green() ? gM : _color.green();
            bM = bM > _color.blue() ? bM : _color.blue();
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));

            double result = (rM / 2) * (1 + (1 / (tan((M_PI * arg) / 2))) * tan(arg * M_PI * (_color.red() / rM - 1 / 2)));
            double r = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (gM / 2) * (1 + (1 / (tan((M_PI * arg) / 2))) * tan(arg * M_PI * (_color.green() / gM - 1 / 2)));
            double g = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = (bM / 2) * (1 + (1 / (tan((M_PI * arg) / 2))) * tan(arg * M_PI * (_color.blue() / bM - 1 / 2)));
            double b = result > 255 ? 255 : (result < 0 ? 0 : result);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalNoLinearPointOperationFinshed((QImage &)(*originImage));
} // tanTransform
