#include "dialogsamplingrate.h"

DialogSamplingRate::DialogSamplingRate(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    // ! 若不设置 dialog 在退出时自动 delete 自己
    // ! 会导致下面第二个 connect 建立重复的映射
    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalSetSamplingRate()));

    // 监听主窗口信号
    // ! 只有这个 connect 会建立重复的映射
    // ! 原因是每次修改采样率时都会 new 一个 dialogSamplingRate
    // ! 但却不会被 delete, 这就导致第 n 次设定采样率时
    // ! 会构造 n 个 dialogSamplingRate, 建立 n 个映射
    // ! 导致出现按照构造顺序重复接收信号, 重复调用槽函数的 Bug
    // ! 例如这里会重复设定采样率的问题
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(setSamplingRate(QImage *)), Qt::UniqueConnection);
}

DialogSamplingRate::~DialogSamplingRate()
{
}

void DialogSamplingRate::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogSamplingRate"));
    this->setFixedSize(400, 112);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addWidget(label, 0, 0, 1, 1);
    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);
    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

    retranslate();

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogSamplingRate::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogSamplingRate", "Dialog", Q_NULLPTR));

    label->setText(QApplication::translate("DialogSamplingRate", "设定采样率", Q_NULLPTR));
} // retranslate

void DialogSamplingRate::emitSignalSetSamplingRate()
{
    int rate = lineEdit->text().toInt();

    if (lineEdit->text().isEmpty())
        return;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定采样率" << rate;
    emit signalSetSamplingRate();
} // emitSignalSetSamplingRate

void DialogSamplingRate::setSamplingRate(QImage *originImage)
{
    int rate = lineEdit->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改采样率" << rate;

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i += rate)
        for (int j = 0; j < height; j += rate)
        {
            int rgb = QRgb(originImage->pixel(i, j));

            for (int p = 0; (p < rate) && ((i + p) < width); p++)
                for (int q = 0; (q < rate) && ((j + q) < height); q++)
                    originImage->setPixel(i + p, j + q, rgb);
        }

    emit signalSetSamplingRateFinished((QImage &)(*originImage));
} // setSamplingRate
