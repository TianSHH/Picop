#include "dialogquantifylevel.h"
#include "../build-Picop-Desktop_Qt_5_9_8_GCC_64bit-Debug/ui_dialogquantifylevel.h"
#include <QDebug>

DialogQuantifyLevel::DialogQuantifyLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogQuantifyLevel)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(emitQuantifyLevelSignal()));
}

DialogQuantifyLevel::~DialogQuantifyLevel()
{
    delete ui;
}

void DialogQuantifyLevel::emitQuantifyLevelSignal()
{
    int level = ui->lineEdit->text().toInt();

    if(ui->lineEdit->text().isEmpty())
        return;

    qDebug() << "设定量化等级" << level;

    emit quantifyLevelSignal(level);
}
