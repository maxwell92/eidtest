#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QByteArray>

#include <dlglogin.h>
#include <dlgreg.h>
#include <user.h>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void saveFile(QString filepath,QString str);
    void encrypt_RSA();
    void setConn();
    
private slots:
    void on_plainText_textChanged();

    void on_encryBtn_clicked();

    void on_sendBtn_clicked();
//    void test();
    void onshowMain();
    void onshowReg();
    void onshowLog();

private:
    Ui::MainWindow *ui;

    QString plainT;
    QString cipherT;
    QString tmp;
    QTcpSocket *client;
    char *chp,*chc,*cht;
    QByteArray ba;
    int n;
    int e1;

//    uint GUID;
//    user *person;
//    QString Ti;
//    QTime *time;

    dlgLogin *logDialog;
    dlgReg *regDialog;

};

#endif // MAINWINDOW_H
