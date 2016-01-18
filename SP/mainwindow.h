#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QByteArray>
#include <reg.h>
#include <logger.h>
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
    void setListen();   //设置监听（注册时）
    void setLogListen(); //设置监听（登录时）
    void setEidListen();
    void decrypt_RSA();

//    void recvClient();
    void sendVeriInfo();   //发送验证信息
    void recvAckInfo();    //接受确认信息
    void enPack();
    void dePack();

    void DES_encry();
    void DES_decry();


    char *hash(char *para1,int len_para1,char *para2,int len_para2);

    void eidOperation();
    void sendIdList();  //发送身份请求信息
    void recvhy1();
    void fMakeK();  //通过M M‘产生K的单向双变量函数
    void writeAck(); //向client写可以进入的确认
signals:
    void writeDataFinish();
private slots:
    void on_listenBtn_clicked();
    void newConn();
    void logConnection();
    void eidConnection();
    void readClient();
    void processOver();
    void onWriteFinish();
    void recvClient();  //接受客户端发送来的注册信息
    void recvLog();   //接受客户端发送来的登录信息
    void recvEid();
//    void recvAck();



//    void on_decryBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString plainT;
    QString cipherT;
    QTcpServer *server;   //注册时用的套接字server端
    QTcpServer *serverSP;  //登录时用的套接字server端
    QTcpServer *serverEID; //登录时用的套接字eid server端
    QTcpSocket *clientEID; //登录时用的套接字eid
    QTcpSocket *clientConn;  //注册用的套接字
    QTcpSocket *clientLog;   //登录用的套接字
    int n;
    int e2;
    char *chp,*chc,*cht;
    QByteArray ba;



    char *regmsg;
    int len_regmsg;
    char *rtnmsg;
    int len_rtnmsg;

    QString regInfo;   //注册消息
    QString rtnInfo;   //注册第二步发送给客户端的返回消息

    QTime ctime;
    QString strTime;

    reg *Register;  //注册对象
    logger *loger;  //登录对象


    QString logInfo;  //登录信息
    char *logMsg;     //登录消息
    int len_logmsg;

    char *id_tmp;  //用于存储和查找的临时id
    int len_idtmp;

    char n0[2];

    char *m1;      //SP产生的M‘
    int len_m1;

    char type[3];   //2位消息类型

    char *SPCert;
    int len_SPCert;

    char *y1;
    int len_y1;

    QString hyInfo;
    char *msghy;
    int len_msghy;

    char *hn01;
    int len_hn01;

    char *hn02;
    int len_hn02;


};

#endif // MAINWINDOW_H
