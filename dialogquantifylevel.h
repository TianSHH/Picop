#ifndef DIALOGQUANTIFYLEVEL_H
#define DIALOGQUANTIFYLEVEL_H

#include <QDialog>

namespace Ui {
class DialogQuantifyLevel;
}

class DialogQuantifyLevel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQuantifyLevel(QWidget *parent = nullptr);
    ~DialogQuantifyLevel();

private:
    Ui::DialogQuantifyLevel *ui;

signals:
    void quantifyLevelSignal(const int &);

private slots:
    void emitQuantifyLevelSignal();
};

#endif // DIALOGQUANTIFYLEVEL_H
