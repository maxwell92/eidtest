#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>
#include <user.h>
#include <dlgreg.h>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class dlgLogin;
}

class dlgLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgLogin(QWidget *parent = 0);
    ~dlgLogin();

    bool check(user *person);  //向服务器发送注册用户数据Id和n0
    void pubS_encry();       //使用SP的公钥S加密
//    void pubS_decry();
    void pubB_encry();       //使用客户端的公钥B加密
//    void pubB_decry();      //使用公钥B解密？？
    void DES_encry();
    void DES_decry();
    void k_encry();          //使用密钥K加密
//    void k_decry();
//    extern void hash();
    void sendIdNo();        //发送登录信息的Id和n0
    void Sendhy1();         //发送h(n0+2)和y1=h^(M-2)(p+Ti)
    void SendeIDClient();   //向eID客户端发送消息
    void connectToSP();     //连接SP服务器
    void fMakeK();          //通过M M‘产生K的单向双变量函数
    void setConnToClient();  //与eID客户端发起通信
    void showIdInfo();
    void saveFile(QString filepath,QString str);
    //哈希函数
    char *hash(char *para1,int len_para1,char *para2,int len_para2);   //hash函数

    user *Person;   //登录对象
    char *pubS;     //SP的公钥
    int len_pubS;   //SP的公钥长度

    char *logmsg;   //登录消息
    int len_logmsg; //登录消息长度
    QString logInfo;//登录信息

    char *n;       //客户端随机产生的n0

    char *n0;    //SP发送来的h(n0+1)的值
    int len_n0;

    QTcpSocket *client;    //准备连接SP的登录时套接字
    QTcpSocket *eIDclient; //准备连接eID客户端的套接字

    char type[3];   //2位的消息类型

    char *msgIdList;  //身份信息
    int len_msgIdList;

    char *msgIdInfo;  //身份请求信息
    int len_msgIdInfo;

    char Ti[9];


    char *SPCert;   //存放有SP地址的证书
    int len_SPCert;

    char *ptmp;    //用于验证的临时p
    short len_ptmp;

    char *mtmp; //由SP发回的新m'
    int len_mtmp;


private slots:
    void on_logBtn_clicked();

    void on_regBtn_clicked();
    void recvSP();
    void recvEClient();
signals:
    void showMain();
    void showReg();
public slots:
   // void onshowLogin();

private:
    Ui::dlgLogin *ui;
};

#endif // DLGLOGIN_H
