#include "dialogsamplingrate.h"
#include "../build-Picop-Desktop_Qt_5_9_8_GCC_64bit-Debug/ui_dialogsamplingrate.h"

DialogSamplingRate::DialogSamplingRate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSamplingRate)
{
    ui->setupUi(this);
}

DialogSamplingRate::~DialogSamplingRate()
{
    delete ui;
}


void DialogSamplingRate::emitSamplingRateSignal()
{
    int rate = ui->lineEdit->text().toInt();

    if(ui->lineEdit->text().isEmpty())
        return;

    emit samplingRateSignal(rate);
}
