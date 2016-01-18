#ifndef DLGREG_H
#define DLGREG_H

#include <QDialog>
#include <user.h>
#include <QString>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class dlgReg;
}

class dlgReg : public QDialog
{
    Q_OBJECT
    
public:
    explicit dlgReg(QWidget *parent = 0);
    ~dlgReg();
    user *Register;
    QTcpSocket *client;

    char *regmsg;
    int len_regmsg;
    char *recvmsg;
    int len_recvmsg;
    char *GUID;
    int len_guid;

    //临时的，用来存储SP返回的信息
    char *guid_t;
    int len_guidt;
    char *name_t;
    int len_namet;
    char *eidnum_t;
    int len_eidnumt;
    char *time_t;
    int len_timet;

    QString regInfo;   //发送给SP的注册消息
    QString recvInfo;  //接受第二步SP发来的消息
    char *y;
    int len_y;

    bool sendRegInfo();  //发送SP消息
    bool recvRegInfo();  //接受SP消息

    //QString enPack(char *regmsg,int len_regmsg,user *reg,char *GUID, int len_guid);
    void enPack();
    void dePack();

    void DES_encry();
    void DES_decry();
    void saveFile(QString filepath,QString str);

    bool verify();
    char *hash(char *p,int len_p,char *time,int len_time);

    void sendRegAck(char *y,bool ack);



private slots:
    void on_submitBtn_clicked();

    void on_returnBtn_clicked();
    void recvVeriInfo();
signals:
    void showLogin();
private:
    Ui::dlgReg *ui;
};

#endif // DLGREG_H
