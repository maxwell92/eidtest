#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dlgpin.h>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enterPin();
    void setListen();
    void saveFile(QString filepath,QString str);
    void connEIDServer();
public slots:
    void showWindow();
    void newConn();
    void recvClnt();
private slots:
    void on_submitBtn_clicked();

private:
    Ui::MainWindow *ui;
    dlgpin *dlgPIN;

    QString clientInfo;
    char *clientmsg;
    int len_clientmsg;

    char *SPCert;
    int len_spcert;
    char *hn02;
    int len_hn02;

    QString eidInfo;
    char *eidMsg;
    int len_eidmsg;

    char *age;
    int len_age;
    char *dep;
    int len_dep;
    char *ins;
    int len_ins;
    char *gen;
    int len_gen;
    char *idnum;
    int len_idnum;
    char *addr;
    int len_addr;
    char *tele;
    int len_tele;
    char *name;
    int len_name;

    QTcpServer *server;
    QTcpSocket *client;  //客户端
    QTcpSocket *eidConn;  //连接eid服务器

    int wndFlg;
};

#endif // MAINWINDOW_H
