#include "dlgpin.h"
#include "ui_dlgpin.h"

dlgpin::dlgpin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgpin)
{
    ui->setupUi(this);
}

dlgpin::~dlgpin()
{
    delete ui;
}

void dlgpin::on_OkBtn_clicked()
{

    this->hide();
    emit(showMain());
}

void dlgpin::on_CancleBtn_clicked()
{
    this->hide();
    emit(showMain());
}
