#include "dialogsamplingrate.h"

DialogSamplingRate::DialogSamplingRate(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalSetSamplingRate()));
}

DialogSamplingRate::~DialogSamplingRate()
{
}

void DialogSamplingRate::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogSamplingRate"));
    this->resize(400, 112);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    retranslate();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

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
    emit signalSetSamplingRate(rate);
} // emitSignalSetSamplingRate
