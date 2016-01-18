#ifndef DLGPIN_H
#define DLGPIN_H

#include <QDialog>

namespace Ui {
class dlgpin;
}

class dlgpin : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgpin(QWidget *parent = 0);
    ~dlgpin();
    
private slots:
    void on_OkBtn_clicked();

    void on_CancleBtn_clicked();
signals:
    void showMain();

private:
    Ui::dlgpin *ui;
};

#endif // DLGPIN_H
