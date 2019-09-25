#ifndef DIALOGSAMPLINGRATE_H
#define DIALOGSAMPLINGRATE_H

#include <QDialog>

namespace Ui {
class DialogSamplingRate;
}

class DialogSamplingRate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSamplingRate(QWidget *parent = nullptr);
    ~DialogSamplingRate();

private:
    Ui::DialogSamplingRate *ui;
};

#endif // DIALOGSAMPLINGRATE_H
