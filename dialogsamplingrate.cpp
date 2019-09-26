#include "dialogsamplingrate.h"
#include "../build-Picop-Desktop_Qt_5_9_8_GCC_64bit-Debug/ui_dialogsamplingrate.h"
#include <QDebug>

DialogSamplingRate::DialogSamplingRate(QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::DialogSamplingRate)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(emitSamplingRateSignal()));
}

DialogSamplingRate::~DialogSamplingRate()
{
    delete ui;
}

void DialogSamplingRate::emitSamplingRateSignal()
{
    int rate = ui->lineEdit->text().toInt();

    if (ui->lineEdit->text().isEmpty())
        return;

    qDebug() << "本次操作采样率" << rate ;

    emit samplingRateSignal(rate);
}
