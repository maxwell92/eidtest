#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <citizen.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setListen();
    void connSP();
    void saveFile(QString filepath,QString str);

private slots:
    void on_startBtn_clicked();
    void recvClient();
    void newClientConn();
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *client;
    QTcpSocket *clientSP;

    QString clientInfo;
    char *clientmsg;
    int len_clientmsg;

    QString spInfo;
    char *spmsg;
    int len_spmsg;

    char *hn02;
    int len_hn02;

    char *SPCert;
    int len_spcert;


    citizen *people;

    char chk[9];
    char *msg;
    int len_msg;
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

};

#endif // MAINWINDOW_H
