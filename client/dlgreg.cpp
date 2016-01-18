#include "dlgreg.h"
#include "ui_dlgreg.h"
#include "QMessageBox"
#include <malloc.h>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QFile>
#include <QTime>

dlgReg::dlgReg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgReg)
{
    ui->setupUi(this);
    this->Register = new user();
    this->client = new QTcpSocket(this);



    len_regmsg = 158; //guid+id+eid+m = 128+20+8+2 = 158
    len_recvmsg = 167;    //guid+id+eid+Ti = 128+20+8+11 = 167;
    len_guid = 129;
    len_y = 7;

    y = (char *)malloc(len_y*sizeof(char));
    memset(y,'\0',len_y);

    regmsg = (char *)malloc(len_regmsg*sizeof(char));
    memset(regmsg,'\0',len_regmsg);

    recvmsg = (char *)malloc(len_recvmsg*sizeof(char));
    memset(recvmsg,'\0',len_recvmsg);

    GUID = (char *)malloc(len_guid*sizeof(char));
    memset(GUID,'a',len_guid-1);
    GUID[len_guid-1] = '\0';
//    int i;
//    for(i=0;i<len_guid;i++)
//    {
//        GUID[i] = 'a';
//    }

//    qDebug()<<GUID<<endl;

    connect(client,SIGNAL(readyRead()),this,SLOT(recvVeriInfo()));
}

dlgReg::~dlgReg()
{
    delete ui;
}

void dlgReg::DES_encry()
{
//     cipherT=QString(QLatin1String(chc));
    regInfo = QString(QLatin1String(regmsg));
}

void dlgReg::DES_decry()
{

}

void dlgReg::saveFile(QString filepath, QString str)
{
    QFile *file = new QFile(filepath);
//    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    if(!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::about(this,"Attention!","File open failed!");
        exit(-1);
    }

    QTextStream txtOutput(file);
    txtOutput<<str<<endl;
    file->close();
}

bool dlgReg::sendRegInfo()
{
    client->connectToHost(QHostAddress::LocalHost,11500);

    char logfile[] = "/home/chen/maxwell/System.log";
    int len_logfile;
    len_logfile = strlen(logfile);
    QString LogFilePath;
    LogFilePath = QString(QLatin1String(logfile));

    QTime currentTime;
    QString logTime;
    char *logtimestr;
    int len_logtimestr=9;
    logtimestr = (char *)malloc(len_logtimestr*sizeof(char));
    memset(logtimestr,'\0',len_logtimestr);
    logTime = currentTime.currentTime().toString();
    QByteArray bTime;
    bTime = logTime.toLatin1();
    memcpy(logtimestr,bTime.data(),logTime.length());

    saveFile(LogFilePath,logTime);

    char sender[] = "client";
    char recver[] = "SP";

    QString stor;
    char *sndtorec;
    int len_sndtorec = 50;
    sndtorec = (char *)malloc(len_sndtorec*sizeof(char));
    memset(sndtorec,'\0',len_sndtorec);

    memcpy(sndtorec,sender,strlen(sender));
    sndtorec[strlen(sender)] = '-';
    sndtorec[strlen(sender)+1] = '>';
    memcpy(sndtorec+strlen(sender)+2,recver,strlen(recver));

    stor = QString(QLatin1String(sndtorec));
    saveFile(LogFilePath,stor);

    saveFile(LogFilePath,regInfo);

    int length=0;
    if((length=client->write(regInfo.toLatin1(),regInfo.length())) != regInfo.length())
    {
        return false;
    }

    return true;
}

void dlgReg::recvVeriInfo()
{
    recvRegInfo();
}

bool dlgReg::recvRegInfo()
{

    recvInfo = client->readAll();
    qDebug()<<"[recvRegInfo]: recvInfo: "<<recvInfo;
    qDebug()<<"[recvRegInfo]: length: "<<recvInfo.length();
    dePack();
    return true;
}

void dlgReg::enPack()
{

    qDebug()<<"[enPack]: enPack():"<<endl;
    qDebug()<<"[enPack]: eIDNum: "<<Register->eIDNum<<endl;
    qDebug()<<"[enPack]: id: "<<Register->id<<endl;
    qDebug()<<"[enPack]: m: "<<Register->m<<endl;
    qDebug()<<"[enPack]: p: "<<Register->p<<endl;

    int len[4];
    len[0] = len_guid-1;
    //len[1] = Register->len_id-1;
    len[1] = strlen(Register->id);
//    len[1] = Register->len_id;

    len[2] = Register->len_eidnum-1;
    len[3] = Register->len_m;

//    qDebug()<<"strlen(id): "<<strlen(Register->id)<<endl;


//    memcpy(regmsg,GUID,len_guid);
    memcpy(regmsg,GUID,len[0]);
    qDebug()<<"[enPack]: GUID: "<<GUID;
    qDebug()<<"[enPack]: regmsg: "<<regmsg;


//    memcpy(regmsg+len_guid,Register->id,Register->len_id);
    memcpy(regmsg+len[0],Register->id,len[1]);
    qDebug()<<"[enPack]: id: "<<Register->id<<"   "<<this->Register->id<<endl;
    qDebug()<<"[enPack]: regmsg: "<<regmsg<<endl;


//    memcpy(regmsg+len_guid+Register->len_id,Register->eIDNum,Register->len_eidnum);
    memcpy(regmsg+len[0]+len[1],Register->eIDNum,len[2]);
    qDebug()<<"[enPack]: eIDNum: "<<Register->eIDNum<<"   "<<this->Register->eIDNum<<endl;
    qDebug()<<"[enPack]: regmsg: "<<regmsg<<endl;


//    memcpy(regmsg+len_guid+Register->len_id+Register->len_eidnum,Register->m,Register->len_m);
    memcpy(regmsg+len[0]+len[1]+len[2],Register->m,len[3]);
    qDebug()<<"[enPack]: m: "<<Register->m<<"   "<<this->Register->m<<endl;
    qDebug()<<"[enPack]: regmsg: "<<regmsg<<endl;
    qDebug()<<"[enPack]: strlen(regmsg)"<<strlen(regmsg)<<endl;
//    QMessageBox::about(this,"problem","problem");



}

bool dlgReg::verify()
{
    qDebug()<<"[verify]: GUID: "<<GUID;
    qDebug()<<"[verify]: guid_t: "<<guid_t;
    qDebug()<<"[verify]: id: "<<Register->id;
    qDebug()<<"[verify]: name_t: "<<name_t;
    qDebug()<<"[verify]: eidnum: "<<Register->eIDNum;
    qDebug()<<"[verify]: eidnum_t: "<<eidnum_t;
    qDebug()<<"[verify]: time: "<<time_t;

//    qDebug()<<strcmp(GUID,guid_t);
//    qDebug()<<strcmp(Register->id,name_t);
//    qDebug()<<strcmp(Register->eIDNum,eidnum_t);

//    if((!strcmp(GUID,guid_t)) && (!strcmp(Register->id,name_t)) && (!strcmp(Register->eIDNum,eidnum_t)))
//    {

//        QMessageBox::about(this,"about","success");

        return true;
//    }
//    this->hide();
//    emit(showLogin());

}

void dlgReg::dePack()
{
    QByteArray b;
    b = recvInfo.toLatin1();
    memcpy(recvmsg,b.data(),recvInfo.length());

//    char *guid_t;
//    int len_guidt=129;
    len_guidt = 129;
    guid_t = (char *)malloc(len_guidt*sizeof(char));
    memset(guid_t,'\0',len_guidt);

//    char *name_t;
//    int len_namet=20;
    len_namet = 20;
    name_t = (char *)malloc(len_namet*sizeof(char));
    memset(name_t,'\0',len_namet);

//    char *eidnum_t;
//    int len_eidnumt=9;
    len_eidnumt = 9;
    eidnum_t = (char *)malloc(len_eidnumt*sizeof(char));
    memset(eidnum_t,'\0',len_eidnumt);

    len_timet = 9;
    time_t = (char *)malloc(len_timet*sizeof(char));
    memset(time_t,'\0',len_timet);

    int len[4];
    len[0] = 128;
    len[2] = 8;  //eidnum
    len[3] = 8;  //time
    len[1] = recvInfo.length()-len[0]-len[2]-len[3]; //

    memcpy(guid_t,recvmsg,len[0]);
    memcpy(name_t,recvmsg+len[0],len[1]);
    memcpy(eidnum_t,recvmsg+len[0]+len[1],len[2]);

    memcpy(time_t,recvmsg+len[0]+len[1]+len[2],len[3]);

    if(verify())
    {
        qDebug()<<"[dePack: ]"<<"Register->p:"<<Register->p<<"time_t:"<<time_t;
        y = hash(Register->p,Register->len_p,time_t,len_timet);  //y0 = hash(P+Ti);
        qDebug()<<"[dePack: ]"<<"y:"<<y;
        qDebug()<<"[dePack]: verify: ";
        sendRegAck(y,true);
    }

    //    this->hide();
    //    emit(showLogin());

}

void dlgReg::sendRegAck(char *y,bool ack)
{
    char *cAck;
    cAck = (char *)malloc(sizeof(char));
    if(ack)
        cAck[0] = '1';
    else
        cAck[0] = '0';
    char ccAck[2];
    ccAck[0] = '1';
    ccAck[1] = '\0';
    char *ackmsg;
    int len_ackmsg;
    len_ackmsg = len_y+1;
    ackmsg = (char *)malloc(len_ackmsg*sizeof(char));
    memset(ackmsg,'\0',len_ackmsg);
    memcpy(ackmsg,y,len_y-1);
    memcpy(ackmsg+len_y-1,ccAck,1);

    QString ackInfo;
    ackInfo = QString(QLatin1String(ackmsg));
    qDebug()<<"[sendRegAck]: ackInfo: "<<ackInfo;
    qDebug()<<"[sendRegAck]: ackInfo len: "<<ackInfo.length();

    char logfile[] = "/home/chen/maxwell/System.log";
    int len_logfile;
    len_logfile = strlen(logfile);
    QString LogFilePath;
    LogFilePath = QString(QLatin1String(logfile));

    QTime currentTime;
    QString logTime;
    char *logtimestr;
    int len_logtimestr=9;
    logtimestr = (char *)malloc(len_logtimestr*sizeof(char));
    memset(logtimestr,'\0',len_logtimestr);
    logTime = currentTime.currentTime().toString();
    QByteArray bTime;
    bTime = logTime.toLatin1();
    memcpy(logtimestr,bTime.data(),logTime.length());

    saveFile(LogFilePath,logTime);

    char sender[] = "client";
    char recver[] = "SP";

    QString stor;
    char *sndtorec;
    int len_sndtorec = 50;
    sndtorec = (char *)malloc(len_sndtorec*sizeof(char));
    memset(sndtorec,'\0',len_sndtorec);

    memcpy(sndtorec,sender,strlen(sender));
    sndtorec[strlen(sender)] = '-';
    sndtorec[strlen(sender)+1] = '>';
    memcpy(sndtorec+strlen(sender)+2,recver,strlen(recver));

    stor = QString(QLatin1String(sndtorec));
    saveFile(LogFilePath,stor);

    saveFile(LogFilePath,ackInfo);








    int length;
    if((length = client->write(ackInfo.toLatin1(),len_ackmsg)) != len_ackmsg)
    {
        QMessageBox::about(this,"error","regist error");
    }
    else
    {
        QMessageBox::about(this,"success","regist success");
        this->hide();
        emit(showLogin());
    }


}

char *dlgReg::hash(char *p,int len_p,char *time,int len_time)
{
    char *tmp;
    int len_tmp;
    len_tmp = len_p+len_time;
    tmp = (char *)malloc(len_tmp*sizeof(char));
    memset(tmp,'\0',len_tmp);

    memcpy(tmp,p,len_p-1);
    memcpy(tmp+len_p-1,time,len_time);
//    简化哈希运算

    char *str;
    int len_str=7;
    str = (char *)malloc(len_str*sizeof(char));
    memset(str,'\0',len_str);

    int i,j;
    int n;
    n = len_tmp/6;
    if(n == 0)
    {
        memset(str,'#',len_str-1);
        memcpy(str,tmp,len_tmp);
        return str;
    }
    else
    {
        for(i=0,j=0;i<len_tmp && j<6;j++,i+=n)
        {
            str[j] = tmp[i];
        }
    }

//    return tmp;
    return str;
}

void dlgReg::on_submitBtn_clicked()
{
    QString str;
    QByteArray b;

    str = ui->eIDRLEdit->text();
    b = str.toLatin1();
//    Register->eIDNum = b.data();
    memcpy(Register->eIDNum,b.data(),Register->len_eidnum);
//    qDebug()<<"eIDNum: "<<Register->eIDNum<<endl;
//    qDebug()<<"eIDNum: "<<this->Register->eIDNum<<endl;

    str = ui->nameRLEdit->text();
    b = str.toLatin1();
//    Register->id = b.data();
//    this->Register->id = b.data();
    memcpy(Register->id,b.data(),Register->len_id);
//    qDebug()<<"id: "<<Register->id<<endl;
//    qDebug()<<"id: "<<this->Register->id<<endl;

    str = ui->mRLEdit->text();
    b = str.toLatin1();
//    Register->m = b.data();
//    this->Register->m = b.data();
    memcpy(Register->m,b.data(),Register->len_m);
//    qDebug()<<"m: "<<Register->m<<endl;
//    qDebug()<<"m: "<<this->Register->m<<endl;

    str = ui->pRLEDit->text();
    b = str.toLatin1();
//    Register->p = b.data();
//    this->Register->p = b.data();
    memcpy(Register->p,b.data(),Register->len_p);
//    qDebug()<<"p: "<<Register->p<<endl;
//    qDebug()<<"p: "<<this->Register->p<<endl;



//    qDebug()<<"submitBtn():"<<endl;
//    qDebug()<<"eIDNum: "<<Register->eIDNum<<endl;
//    qDebug()<<"id: "<<Register->id<<endl;
//    qDebug()<<"m: "<<Register->m<<endl;
//    qDebug()<<"p: "<<Register->p<<endl;


    enPack();
    DES_encry();
//    qDebug()<<"length: "<<regInfo.length();
    if(!sendRegInfo())
    {
        QMessageBox::warning(this,"warning","发送失败，请检查网络！");
    }

//    QMessageBox::about(this,"problem1","problem1");

//    this->hide();
//    emit(showLogin());
}

void dlgReg::on_returnBtn_clicked()
{
    this->hide();
    emit(showLogin());
}

