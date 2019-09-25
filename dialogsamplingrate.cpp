#include "dialogsamplingrate.h"
#include "ui_dialogsamplingrate.h"

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
