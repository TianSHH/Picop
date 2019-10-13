#include "dialognolinearpointoperation.h"

DialogNolinearPointOperation::DialogNolinearPointOperation(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalNolinearPointOperation()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(transformTypeSwitch(transformType, QImage *)));
}

DialogNolinearPointOperation::~DialogNolinearPointOperation()
{
}

void DialogNolinearPointOperation::transformTypeSwitch(QString transformType, QImage *originImage)
{
    if (transformType == "nolinearGrayscaleTransform")
        nolinearGrayscaleTransform(originImage);
    else if (transformType == "sinTransform")
    {
    }
    else if (transformType == "tanTransform")
    {
    }
} // transformTypeSwitch

void DialogNolinearPointOperation::setupNolinearGrayscaleTransform()
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

    transformType = "nolinearGrayscaleTransform";
}

void DialogNolinearPointOperation::emitSignalNolinearPointOperation()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定非线性点运算参数";

    emit signalNoLinearPointOperation();
}

void DialogNolinearPointOperation::nolinearGrayscaleTransform(QImage *originImage)
{
    double var = lineEditVar->text().toDouble();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行非线性灰度变换"
                       << "参数:" << var;

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

            double result = _color.red() + var * _color.red() * (rM - _color.red());
            double r = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = _color.green() + var * _color.green() * (gM - _color.green());
            double g = result > 255 ? 255 : (result < 0 ? 0 : result);

            result = _color.blue() + var * _color.blue() * (bM - _color.blue());
            double b = result > 255 ? 255 : (result < 0 ? 0 : result);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalNoLinearPointOperationFinshed((QImage &)(*originImage));
} // nolinearGrayscaleTransform
