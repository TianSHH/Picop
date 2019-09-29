#include "dialogquantifylevel.h"

DialogQuantifyLevel::DialogQuantifyLevel(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalSetQuantifyLevel()));
}

DialogQuantifyLevel::~DialogQuantifyLevel()
{
}

void DialogQuantifyLevel::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogQuantifyLevel"));
    this->resize(400, 112);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

    retranslate();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogQuantifyLevel::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogQuantifyLevel", "Dialog", Q_NULLPTR));
    label->setText(QApplication::translate("DialogQuantifyLevel", "输入量化等级", Q_NULLPTR));
} // retranslate

void DialogQuantifyLevel::emitSignalSetQuantifyLevel()
{
    int level = lineEdit->text().toInt();

    if (lineEdit->text().isEmpty())
        return;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定量化等级" << level;

    emit signalSetQuantifyLevel(level);
} // emitSignalSetQuantifyLevel
