#include "dialoglogtransformation.h"

DialogLogTransformation::DialogLogTransformation(QWidget *parent) : QDialog(parent)
{
    setup();

    setAttribute(Qt::WA_DeleteOnClose);

    paintFunctionImage(doubleSpinBoxArgA->value(), doubleSpinBoxArgB->value(), doubleSpinBoxArgC->value());

    connect(doubleSpinBoxArgA, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgA_valueChanged(double)));
    connect(doubleSpinBoxArgB, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgB_valueChanged(double)));
    connect(doubleSpinBoxArgC, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgC_valueChanged(double)));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalLogTransformationStart()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(logTransformation(QImage *)));
}

DialogLogTransformation::~DialogLogTransformation()
{
}

void DialogLogTransformation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogLogTrans"));
    this->setFixedSize(400, 300);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    labelArgA = new QLabel(this);
    labelArgA->setObjectName(QStringLiteral("labelArgA"));

    labelArgB = new QLabel(this);
    labelArgB->setObjectName(QStringLiteral("labelArgB"));

    labelArgC = new QLabel(this);
    labelArgC->setObjectName(QStringLiteral("labelArgC"));

    doubleSpinBoxArgA = new QDoubleSpinBox(this);
    doubleSpinBoxArgA->setObjectName(QStringLiteral("doubleSpinBoxArgA"));
    doubleSpinBoxArgA->setValue(1);

    doubleSpinBoxArgB = new QDoubleSpinBox(this);
    doubleSpinBoxArgB->setObjectName(QStringLiteral("doubleSpinBoxArgB"));
    doubleSpinBoxArgB->setValue(0);

    doubleSpinBoxArgC = new QDoubleSpinBox(this);
    doubleSpinBoxArgC->setObjectName(QStringLiteral("doubleSpinBoxArgC"));
    doubleSpinBoxArgC->setValue(1);

    customPlot = new QCustomPlot(this);
    customPlot->setObjectName(QStringLiteral("customPlot"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal); // 设置 buttonBox 内部的布局
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(labelArgA, 0, 0);
    gridLayout->addWidget(labelArgB, 1, 0);
    gridLayout->addWidget(labelArgC, 2, 0);
    gridLayout->addWidget(doubleSpinBoxArgA, 0, 1);
    gridLayout->addWidget(doubleSpinBoxArgB, 1, 1);
    gridLayout->addWidget(doubleSpinBoxArgC, 2, 1);
    gridLayout->addWidget(customPlot, 0, 2, 3, 4); // 高度3行, 宽度4列
    gridLayout->addWidget(buttonBox, 3, 0, 1, 6);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);

    retranslate();
} // setup

void DialogLogTransformation::retranslate()
{
    this->setWindowTitle("设定对数变换参数");

    labelArgA->setText(QApplication::translate("设定弯曲程度", "a ", Q_NULLPTR));
    labelArgB->setText(QApplication::translate("设定上下偏移量", "b ", Q_NULLPTR));
    labelArgC->setText(QApplication::translate("设定常数", "c ", Q_NULLPTR));
} // retranslate

void DialogLogTransformation::paintFunctionImage(double a, double b, double c)
{
    QVector<double> x(5101), y(5101);

    for (int i = 0; i < 5101; ++i)
    {
        x[i] = i / 20.0;
        y[i] = c * qLn(1 + a * x[i] / 255) / qLn(a + 1) * 255 + b;
    }

    // 创建图像并分配数据
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, 255);
    customPlot->replot();
} // paintFunctionImage

void DialogLogTransformation::on_doubleSpinBoxArgA_valueChanged(double arg)
{
    paintFunctionImage(arg, doubleSpinBoxArgB->value(), doubleSpinBoxArgC->value());
} // on_doubleSpinBoxArgA_valueChanged

void DialogLogTransformation::on_doubleSpinBoxArgB_valueChanged(double arg)
{
    paintFunctionImage(doubleSpinBoxArgA->value(), arg, doubleSpinBoxArgC->value());
} // on_doubleSpinBoxArgB_valueChanged

void DialogLogTransformation::on_doubleSpinBoxArgC_valueChanged(double arg)
{
    paintFunctionImage(doubleSpinBoxArgA->value(), doubleSpinBoxArgB->value(), arg);
} // on_doubleSpinBoxArgC_valueChanged

void DialogLogTransformation::logTransformation(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行对数变换,"
                       << "弯曲程度" << doubleSpinBoxArgA->value() << ","
                       << "上下偏移量" << doubleSpinBoxArgB->value() << ","
                       << "常数" << doubleSpinBoxArgC->value() << ",";

    int width = originImage->width();
    int height = originImage->height();

    // QImage *newImage = new QImage(width, height, QImage::Format_ARGB32);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = QColor(originImage->pixel(i, j));

            // ! logx(y)=ln(y)/ln(x)
            // y = c * log(b + 1)(1 + b * x / 255) * 255

            int r = doubleSpinBoxArgC->value() * qLn(1 + doubleSpinBoxArgA->value() * color.red() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255 + doubleSpinBoxArgB->value();
            int g = doubleSpinBoxArgC->value() * qLn(1 + doubleSpinBoxArgA->value() * color.green() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255 + doubleSpinBoxArgB->value();
            int b = doubleSpinBoxArgC->value() * qLn(1 + doubleSpinBoxArgA->value() * color.blue() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255 + doubleSpinBoxArgB->value();

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalLogTransformationEnd((QImage &)(*originImage));
} // logTrans

void DialogLogTransformation::emitSignalLogTransformationStart()
{
    emit signalLogTransformationStart();
} // emitSignalLogTransStart
