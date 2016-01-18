#include "dlglogin.h"
#include "ui_dlglogin.h"
#include "QMessageBox"
#include <malloc.h>
#include <QHostAddress>
#include <QDebug>
#include <QFile>
#include <QTime>


dlgLogin::dlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgLogin)
{
    ui->setupUi(this);
    Person = new user();

    len_SPCert = 20;
    SPCert = (char *)malloc(len_SPCert*sizeof(char));
    memset(SPCert,'\0',len_SPCert);

    len_pubS = 10;
    pubS = (char *)malloc(len_pubS*sizeof(char));
    memset(pubS,'\0',len_pubS);

    len_logmsg = 100;
    logmsg = (char *)malloc(len_logmsg*sizeof(char));
    memset(logmsg,'\0',len_logmsg);

    len_msgIdInfo = 2;   //身份请求信息   //拿数字表示 或者拿位表示
    msgIdInfo = (char *)malloc(len_msgIdInfo*sizeof(char));
    memset(msgIdInfo,'\0',len_msgIdInfo);
//    msgIdInfo[0] = 27;   // 0001 1011 意味：性别，身份证号，联系电话，真实姓名


    len_ptmp = 7;
    ptmp = (char *)malloc(len_ptmp*sizeof(char));
    memset(ptmp,'\0',len_ptmp);

    len_mtmp = 2;
    mtmp = (char *)malloc(len_mtmp*sizeof(char));
    memset(mtmp,'\0',len_mtmp);

    memset(Ti,'\0',9);

    n = (char *)malloc(sizeof(char));
    n[0] = 'n';    //随机数

    len_n0 = 7;
    n0 = (char *)malloc(len_n0*sizeof(char));
    memset(n0,'\0',len_n0);

    client = new QTcpSocket(this);
    connect(client,SIGNAL(readyRead()),this,SLOT(recvSP()));

    eIDclient = new QTcpSocket(this);


    connect(eIDclient,SIGNAL(readyRead()),this,SLOT(recvEClient()));

    memset(type,'\0',3);
}

dlgLogin::~dlgLogin()
{
    delete ui;
}

void dlgLogin::connectToSP()
{
    client->connectToHost(QHostAddress::LocalHost,12500);

}

bool dlgLogin::check(user *person)
{
    //连接SP进行验证
    QString str;
    QByteArray b;
    str = ui->nameLEdit->text();
    b = str.toLatin1();
    memcpy(person->id,b.data(),str.length());
    qDebug()<<"[check: ]"<<"connecting...";
    connectToSP();
    qDebug()<<"[check: ]"<<"sendIdNo...";
    sendIdNo();
    qDebug()<<"[check: ]"<<"sendIdNo over";



    return true;
}

void dlgLogin::pubS_encry()
{

}

void dlgLogin::saveFile(QString filepath, QString str)
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


void dlgLogin::sendIdNo()
{
    char *msgIdNo;
    int len_msgIdNo;
//    char type[2] = {'0','1'};
    type[0] = '0';
    type[1] = '1';
    QString messageIdNo;

    len_msgIdNo = 2+1+Person->len_id+1;  // type+n+id+'\0'
    msgIdNo = (char *)malloc(len_msgIdNo*sizeof(char));
    memset(msgIdNo,'\0',len_msgIdNo);

    memcpy(msgIdNo,type,2);
    memcpy(msgIdNo+2,n,1);
    memcpy(msgIdNo+2+1,Person->id,strlen(Person->id));

    messageIdNo = QString(QLatin1String(msgIdNo));

    qDebug()<<"[sendIdNo: ]"<<"messageIdNo: "<<messageIdNo;

    pubS_encry();

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

    saveFile(LogFilePath,messageIdNo);





    int length;
    if((length = client->write(messageIdNo.toLatin1(),messageIdNo.length())) != messageIdNo.length())
    {
        QMessageBox::about(this,"error","write error!");
        qDebug()<<"[sendInNo: ]"<<"socket write error!";
    }
}

void dlgLogin::on_logBtn_clicked()
{

    if(check(Person))
    {
        //本地文件


//        this->destroy(true);
//        emit(showMain());
    }
    else
    {
        QMessageBox::warning(this,"Warning","nothing");
    }

}

void dlgLogin::on_regBtn_clicked()
{
    //this->destroy(true);
    this->hide();
    emit(showReg());
}

void dlgLogin::recvSP()
{
//        connectToSP();                              //**********************************************************************//
    QString str;
    str = client->readAll();

    qDebug()<<"[recvSP: ]"<<"received str: "<<str;

    char *strtmp;
    int len_strtmp = str.length()+1;
    strtmp = (char *)malloc(len_strtmp*sizeof(char));
    memset(strtmp,'\0',len_strtmp);
    QByteArray b;
    b = str.toLatin1();
    memcpy(strtmp,b.data(),len_strtmp);

    qDebug()<<"[recvSP: ]"<<"received msg: "<<strtmp;

    char typetmp[3];
    memset(typetmp,'\0',3);
    memcpy(typetmp,strtmp,2);

    int len[7];

    if(typetmp[0] == '0' && typetmp[1] == '2')
    {
        len_msgIdList = str.length()+1;

        msgIdList = (char *)malloc(len_msgIdList*sizeof(char)); //SP发来的身份信息
        memset(msgIdList,'\0',len_msgIdList);
        QByteArray b;
        b = str.toLatin1();
        memcpy(msgIdList,b.data(),len_msgIdList);  //包含着2个长度的type
        qDebug()<<"[recvSP: ]"<<"received str: "<<str;
        qDebug()<<"[recvSP: ]"<<"msgIdList: "<<msgIdList;

        len[0] = Person->len_eidnum-1;    //8
        len[1] = len_n0-1;         //6
        len[2] = len_msgIdInfo-1;  //1
        len[3] = len_SPCert-1;  //19
        len[5] = 8;             //SP返回的时间长度为8
        len[6] = len_mtmp-1;    //8
        len[4] = str.length()-2 -len[0]-len[1]-len[2]-len[3]-len[5]-len[6];


        memcpy(Person->eIDNum,msgIdList+2,len[0]);  //8

        qDebug()<<"[recvSP: ]"<<"person->eidnum:"<<Person->eIDNum;

        memcpy(n0,msgIdList+2+len[0],len[1]);//len_n0-1 = 6
        qDebug()<<"[recvSP: ]"<<"n0:"<<n0;

        memcpy(msgIdInfo,msgIdList+2+len[0]+len[1],len[2]);//1;
        qDebug()<<"[recvSP: ]"<<"msgIdInfo: "<<msgIdInfo;

        memcpy(SPCert,msgIdList+2+len[0]+len[1]+len[2],len[3]); //19
        qDebug()<<"[recvSP: ]"<<"SPCert: "<<SPCert;

        memcpy(Person->id,msgIdList+2+len[0]+len[1]+len[2]+len[3],len[4]); //7
        qDebug()<<"[recvSP: ]"<<"person->id:"<<Person->id;

        memcpy(Ti,msgIdList+2+len[0]+len[1]+len[2]+len[3]+len[4],len[5]); //8
        qDebug()<<"[recvSP: ]"<<"Ti: "<<Ti;

        memcpy(mtmp,msgIdList+2+len[0]+len[1]+len[2]+len[3]+len[4]+len[5],len[6]);//1
        qDebug()<<"[recvSP: ]"<<"mtmp: "<<mtmp;
        QString str2;
        QByteArray b2;

        str2 = ui->pwdLEdit_2->text();
        b2 = str2.toLatin1();
        memcpy(Person->p,b2.data(),str2.length());

        str2 = ui->mLEdit_3->text();
        b2 = str2.toLatin1();
        memcpy(Person->m,b2.data(),str2.length());


        Sendhy1();

        SendeIDClient();

    }
    else if(typetmp[0] == '0' && typetmp[1] == '4')
    {

        char ack[2];
        memset(ack,'\0',2);
        memcpy(ack,strtmp+2,1);
        qDebug()<<"[recvSP:]"<<"type 04";
        if(ack[0] == 'y')
        {
            this->destroy(true);
            emit(showMain());

            qDebug()<<"[recvSP:]"<<"log success";
        }
        else
        {
            qDebug()<<"[recvSP:]"<<"ack receive error";
        }
    }
}

void dlgLogin::fMakeK()
{

}

//char *dlgLogin::hash(char *para1, int len_para1, char *para2, int len_para2)
//{
//    char *tmp;
//    int len_tmp;
//    len_tmp = len_para1+len_para2;
//    tmp = (char *)malloc(len_tmp*sizeof(char));
//    memcpy(tmp,para1,len_para1-1);
//    memcpy(tmp+len_para1-1,para2,len_para2);
//    /*
//      缺少真实哈希运算
//    */

////    return tmp;
////    return p;
//}


char *dlgLogin::hash(char *p,int len_p,char *time,int len_time)
{
    char *tmp;
    int len_tmp;
    len_tmp = len_p+len_time;
    tmp = (char *)malloc(len_tmp*sizeof(char));
    memset(tmp,'\0',len_tmp);

    memcpy(tmp,p,len_p);
    memcpy(tmp+len_p,time,len_time);
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
//        memset(str+len_tmp,'#',6-len_tmp);
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

void dlgLogin::k_encry()
{

}

void dlgLogin::Sendhy1()
{
    char *msghy;
    int len_hymsg;

    char add[2];   //n0要+的2
    add[0] = '2';
    add[1] = '\0';

    //h(n0+2);
    char *msgHash;
    int len_msgHash=7;
//    msgHash = (char *)malloc(6*sizeof(char));
    msgHash = (char *)malloc(len_msgHash*sizeof(char));
    memset(msgHash,'\0',len_msgHash);
    msgHash = hash(n,1,add,1);   //注意n的长度只有1

    qDebug()<<"[Sendhy1: ]"<<"msgHash: "<<msgHash;

    //h(P+Ti);
    char *msgy1;
    int len_msgy1;
//    len_msgy1 = Person->len_p-1+9-1;
    len_msgy1 = 7;
    msgy1 = (char *)malloc(len_msgy1*sizeof(char));
    memset(msgy1,'\0',len_msgy1);
    msgy1=hash(Person->p,Person->len_p-1,Ti,8); //注意Ti的长度为9  //hash函数运算M-2次,此处省略
//    len_msgy1 = strlen(msgy1);

    qDebug()<<"[Sendhy1: ]"<<"msgy1: "<<msgy1;

    memset(type,'\0',3);
    type[0] = '0';
    type[1] = '3';

    len_hymsg = 2+strlen(msgHash)+len_msgy1;
    msghy = (char *)malloc(len_hymsg*sizeof(char));
    memcpy(msghy,type,2);
    memcpy(msghy+2,msgHash,strlen(msgHash));
    memcpy(msghy+2+strlen(msgHash),msgy1,len_msgy1);
    //拷贝type, msgHash 和  msgy1 到msghy里

    qDebug()<<"[Sendhy1: ]"<<"msghy: "<<msghy;

    k_encry();

    QString hyInfo;
    hyInfo = QString(QLatin1String(msghy));

    qDebug()<<"[Sendhy1: ]"<<"hyInfo: "<<hyInfo;


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

    saveFile(LogFilePath,hyInfo);


    int length;
    if((length = client->write(hyInfo.toLatin1(),hyInfo.length())) != hyInfo.length())
    {
        qDebug()<<"[Sendhy1: ]"<<"write socket error";
        QMessageBox::about(this,"error","Sendhy1");
    }


}

void dlgLogin::setConnToClient()
{
    eIDclient->connectToHost(QHostAddress::LocalHost,13500);
}

void dlgLogin::recvEClient()
{

}

void dlgLogin::showIdInfo()
{
    QString ndMsg;
    char *ndInfo;
    int len_ndInfo=500;
    ndInfo = (char *)malloc(len_ndInfo*sizeof(char));
    memset(ndInfo,'\0',len_ndInfo);


    char bin[8];
    memset(bin,0,8);
    int tmp;
    int i=0;
    tmp = msgIdInfo[0];
    while(1)
    {
        if(tmp < 2)
        {
            bin[i] = tmp%2;
            break;
        }

        bin[i] = tmp % 2;
        tmp = tmp / 2;
        i++;
    }
    qDebug()<<"[showIdInfo]: ";
    int j;
    for(j=0;j<8;j++)
    {
        qDebug()<<"bin["<<j<<"]:"<<bin[j];
    }

    int tmplen=0;
    if(bin[0] == 1)
    {
//        char msg[] = "真实姓名";
        char msg1[] = " Name ";

        memcpy(ndInfo+tmplen,msg1,strlen(msg1));
        tmplen+=strlen(msg1);

    }

    if(bin[1] == 1)
    {
//        char msg[] = "联系电话";
        char msg2[] = " Telephone_Number ";

        memcpy(ndInfo+tmplen,msg2,strlen(msg2));
        tmplen+=strlen(msg2);
    }

    if(bin[2] == 1)
    {
//        char msg[] = "家庭地址";
        char msg3[] = " Family_Address ";

        memcpy(ndInfo+tmplen,msg3,strlen(msg3));
        tmplen+=strlen(msg3);
    }

    if(bin[3] == 1)
    {
//        char msg[] = "身份证号";
        char msg4[] = " Identity_Number ";

        memcpy(ndInfo+tmplen,msg4,strlen(msg4));
        tmplen+=strlen(msg4);
    }

    if(bin[4] == 1)
    {
//        char msg[] = "性别";
        char msg5[] = " Gender ";

        memcpy(ndInfo+tmplen,msg5,strlen(msg5));
        tmplen+=strlen(msg5);
    }

    if(bin[5] == 1)
    {
//        char msg[] = "社保号码";
        char msg6[] = " Insurance_Number ";

        memcpy(ndInfo+tmplen,msg6,strlen(msg6));
        tmplen+=strlen(msg6);
    }

    if(bin[6] == 1)
    {
//        char msg[] = "工作单位";
        char msg7[] = " Department ";

        memcpy(ndInfo+tmplen,msg7,strlen(msg7));
        tmplen+=strlen(msg7);
    }

    if(bin[7] == 1)
    {
//        char msg[] = "年龄";
        char msg8[] = " Age ";

        memcpy(ndInfo+tmplen,msg8,strlen(msg8));
        tmplen+=strlen(msg8);
    }

    ndMsg = QString(QLatin1String(ndInfo));
    qDebug()<<"[showIdInfo: ]"<<"ndMsg: "<<ndMsg;
    QMessageBox::about(this,"Tips",ndMsg);
    qDebug()<<"[ShowIdInfo: ]"<<"It's ok";
}

void dlgLogin::SendeIDClient()
{
//    char *msgStart;
//    int len_msgStart;

    setConnToClient();

    showIdInfo();

    memset(type,'\0',3);
    type[0] = '1';
    type[1] = '0';



    char add[2];
    add[0] = '2';
    add[1] = '\0';
    char *msgHash;
    msgHash = (char *)malloc(6*sizeof(char));
    msgHash = hash(n,1,add,1);   //注意n的长度只有1
    qDebug()<<"[sendeIDClient: ]"<<"msgHash: "<<msgHash;

    //添加SPCert证书




    int len_eidmsg;
    char *eidmsg;

    len_eidmsg = 2+6+19;
    eidmsg =  (char *)malloc(len_eidmsg*sizeof(char));
    memset(eidmsg,'\0',len_eidmsg);

    memcpy(eidmsg,type,2);
    memcpy(eidmsg+2,SPCert,len_SPCert-1);
    memcpy(eidmsg+2+len_SPCert-1,msgHash,6);

    qDebug()<<"[sendeIDClient: ]"<<"eidmsg:"<<eidmsg;

    QString StartInfo;
    StartInfo = QString(QLatin1String(eidmsg));
    qDebug()<<"[sendeIDClient: ]"<<"StartInfo:"<<StartInfo;


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
    char recver[] = "eidClient";

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

    saveFile(LogFilePath,StartInfo);

//    char testwords[3];
//    testwords[0] = 'o';
//    testwords[1] = '1';
//    testwords[2] = '2';

//    QString testinfo;
//    testinfo = QString(QLatin1String(testwords));


//    int length;
//    if((length = eIDclient->write(StartInfo.toLatin1(), StartInfo.length())) != StartInfo.length())
//    {
//        qDebug()<<"[sendeIDClient: ]"<<"write error!";
//    }
//    qDebug()<<"[sendeIDClient: "<<"write over";


    int length;
    if((length = eIDclient->write(StartInfo.toLatin1(),StartInfo.length())) != StartInfo.length())
    {
        qDebug()<<"[sendeIDClient: ]"<<"write error!";
    }
     qDebug()<<"[sendeIDClient: ]"<<"write over";

}



/*
void dlgLogin::onshowLogin()
{
    this->show();
}
*/
