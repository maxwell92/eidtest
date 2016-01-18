#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <math.h>
#include <reg.h>
#include <malloc.h>
#include <QTime>
#include <QDebug>

#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

#define NEW_CHAR_DECODE(ch,nch) {if(nch>=1 && nch<=26) {ch=nch+96;} else if(nch == 27) {ch = ' ';} else {ch = '\0';}}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    len_SPCert = 20;
    SPCert = (char *)malloc(len_SPCert * sizeof(char));
    memset(SPCert,'\0',len_SPCert);
    //对SPCert的初始化
    memset(SPCert,'b',len_SPCert-1);

    Register = new reg();
    loger = new logger();

    len_regmsg = 158; //guid+id+eid+m: 128+20+8+2
    regmsg = (char *)malloc(len_regmsg*sizeof(char));
    memset(regmsg,'\0',len_regmsg);

    len_rtnmsg = 167;         //guid+id+eid+time:128+20+8+8=164
    rtnmsg = (char *)malloc(len_rtnmsg*sizeof(char));
    memset(rtnmsg,'\0',len_rtnmsg);

    server = new QTcpServer(this);
    serverSP = new QTcpServer(this);
    serverEID = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConn()));
    connect(serverSP,SIGNAL(newConnection()),this,SLOT(logConnection()));
    connect(serverEID,SIGNAL(newConnection()),this,SLOT(eidConnection()));
    n=33;
    e2=7;

    connect(this,SIGNAL(writeDataFinish()),this,SLOT(onWriteFinish()));


    len_logmsg = 200;
    logMsg = (char *)malloc(len_logmsg*sizeof(char));
    memset(logMsg,'\0',len_logmsg);

    len_idtmp = 20;
    id_tmp = (char *)malloc(len_idtmp*sizeof(char));
    memset(id_tmp,'\0',len_idtmp);

    memset(n0,'\0',2);

    len_m1 = 3;
    m1 = (char *)malloc(len_m1*sizeof(char));
    memset(m1,'\0',len_m1);
    m1[0] = '9';
    m1[1] = '9';

//    len_y1 = ;
//    y1 = (char *)malloc(len_y1*sizeof(char));
//    memset(y1,'\0',len_y1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onWriteFinish()
{
    sendVeriInfo();   //向客户端发送验证消息
}

void MainWindow::DES_encry()
{

}

void MainWindow::DES_decry()
{

}

void MainWindow::sendVeriInfo()
{
    enPack();
//    QTcpSocket *client;
//    client = new QTcpSocket(this);
    rtnInfo = QString(QLatin1String(rtnmsg));

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

    char sender[] = "SP";
    char recver[] = "client";

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

    saveFile(LogFilePath,rtnInfo);













    int length;
    if((length=clientConn->write(rtnInfo.toLatin1(),rtnInfo.length())) != rtnInfo.length())
    {
//        return false;
        qDebug()<<"[sendVeriInfo]: clientConn write error";
    }
//    return true;
//    recvAckInfo();
}

//void MainWindow::recvAck()
//{
//    qDebug()<<"recvAck: ";
//    recvAckInfo();
//}

void MainWindow::recvAckInfo()
{
    char *ackmsg;    //y0 = hash(P+Ti);
    int len_ackmsg = Register->len_y+1;
    ackmsg = (char *)malloc(len_ackmsg*sizeof(char));
    memset(ackmsg,'\0',len_ackmsg);

    qDebug()<<"[recvAckInfo]:";

    QString ackInfo;
//    ackInfo = clientConn->readAll();
//    ackInfo = clientConn->readAll();
    ackInfo = regInfo;
    qDebug()<<"[recvAckInfo]: ackInfo: "<<ackInfo;

    QByteArray b;
    b = ackInfo.toLatin1();
    memcpy(ackmsg,b.data(),len_ackmsg);
    qDebug()<<"[recvAckInfo]: ackmsg: "<<ackmsg;
    qDebug()<<"[recvAckInfo]: len_ackmsg: "<<len_ackmsg;

    memcpy(Register->y,ackmsg,Register->len_y-1);  //将客户端计算的y0存到register里 也应该写入文件
    qDebug()<<"[recvAckInfo]: Register->y: "<<Register->y;

    char msg[10] = "registed!";
    msg[9] = '\0';
    char *message;
    message = (char *)malloc((strlen(msg)+strlen(Register->name)+2)*sizeof(char));

    memcpy(message,Register->name,strlen(Register->name));
    message[strlen(Register->name)] = ' ';
    memcpy(message+strlen(Register->name)+1,msg,strlen(msg));
    QString strMsg;
    strMsg = QString(QLatin1String(message));
    ui->cipherText->appendPlainText(strMsg);
    saveFile(ui->logFilepath->toPlainText(),strMsg);

    strMsg = QString(QLatin1String(ackmsg));
    saveFile(ui->dataFilepath->toPlainText(),strMsg); //将y0写入文件


    strMsg = QString(QLatin1String(Register->rtime));
    saveFile(ui->dataFilepath->toPlainText(),strMsg); //将注册时间reg_time写入文件

    clientConn->close();
}

void MainWindow::enPack()
{

    QByteArray b;
    b = strTime.toLatin1();
    memcpy(Register->rtime,b.data(),strTime.length());

    int len[4];
    len[0] = Register->len_guid-1;
//    len[1] = Register->len_name;
    len[1] = strlen(Register->name);
    len[2] = Register->len_eidnum-1;
    len[3] = Register->len_time;

    memcpy(rtnmsg,Register->guid,len[0]);
    memcpy(rtnmsg+len[0],Register->name,len[1]);
    memcpy(rtnmsg+len[0]+len[1],Register->eIDNum,len[2]);
    memcpy(rtnmsg+len[0]+len[1]+len[2],Register->rtime,len[3]);

    qDebug()<<"[enPack]: rtnmsg: "<<rtnmsg;

}

void MainWindow::dePack()
{
    int len[4];
    len[0] = Register->len_guid-1;
    len[3] = Register->len_m-1;
    len[2] = Register->len_eidnum-1;
    len[1] = regInfo.length() - len[0] - len[2] - len[3];

    memcpy(Register->guid,regmsg,len[0]);
    Register->guid[Register->len_guid] = '\0';

    memcpy(Register->name,regmsg+len[0],len[1]);
    Register->name[Register->len_name] = '\0';

    memcpy(Register->eIDNum,regmsg+len[0]+len[1],len[2]);
    Register->eIDNum[Register->len_eidnum] = '\0';

    memcpy(Register->m,regmsg+len[0]+len[1]+len[2],len[3]);
    Register->m[Register->len_m] = '\0';


    qDebug()<<"[dePack]: guid: "<<Register->guid;
    qDebug()<<"[dePack]: name: "<<Register->name;
    qDebug()<<"[dePack]: eIDNum: "<<Register->eIDNum;
    qDebug()<<"[dePack]: m: "<<Register->m;


    QString data;

    data = QString(QLatin1String(Register->name));
    saveFile(ui->dataFilepath->toPlainText(),data);
    data = QString(QLatin1String(Register->eIDNum));
    saveFile(ui->dataFilepath->toPlainText(),data);
 ;
//    data = QString(QLatin1String(Register->rtime));
//    saveFile(ui->dataFilepath->toPlainText(),data);
    data = QString(QLatin1String(Register->guid));
    saveFile(ui->dataFilepath->toPlainText(),data);
    data = QString(QLatin1String(Register->m));
    saveFile(ui->dataFilepath->toPlainText(),data);





    emit(writeDataFinish());
}





void MainWindow::saveFile(QString filepath, QString str)
{
    QFile *file = new QFile(filepath);
   // if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    if(!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::about(this,"Attention!","File open failed!");
        exit(-1);
    }

    QTextStream txtOutput(file);
    txtOutput<<str<<endl;
    file->close();
}

void MainWindow::setListen()
{
    if(!server->isListening())
    {
        if(!server->listen(QHostAddress::Any,11500))
        {
            QMessageBox::about(this,"Attention!","正在监听！");
        }
    }

}

void MainWindow::setLogListen()
{
    if(!serverSP->isListening())
    {
        if(!serverSP->listen(QHostAddress::Any,12500))
        {
            QMessageBox::about(this,"Attention!","正在监听！");
        }
    }
}

void MainWindow::setEidListen()
{
    if(!serverEID->isListening())
    {
        if(!serverEID->listen(QHostAddress::Any,10500))
        {
            QMessageBox::about(this,"Attention","listening...");
        }
    }
}

void MainWindow::newConn()
{
    QString message;
    //char *msg = "new arrival";
    char msg[] = "new arrival";

    //QMessageBox::about(this,"Attention!","New Connection Setup!");
    message=QString(QLatin1String(msg));
    ui->cipherText->appendPlainText(message);

    strTime = ctime.currentTime().toString();
    Register->reg_time = strTime;
    qDebug()<<"[newConn]: time: "<<strTime<<endl;
    saveFile(ui->logFilepath->toPlainText(),strTime);

    clientConn = server->nextPendingConnection();

    connect(clientConn,SIGNAL(disconnected()),clientConn,SLOT(deleteLater()));
    //connect(clientConn,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(clientConn,SIGNAL(readyRead()),this,SLOT(recvClient()));
//    connect(clientConn,SIGNAL(readyRead()),this,SLOT(recvAck()));
}

void MainWindow::recvClient()
{
    regInfo = clientConn->readAll();

    qDebug()<<"[recvClient]: regInfo"<<regInfo;
    qDebug()<<"[recvClient]: regInfo length: "<<regInfo.length(); 
    if(regInfo.length() < Register->len_guid)    //如果消息长度小于最长的GUID的话，判定是注册第三步的确认消息
    {
        memset(regmsg,'\0',regInfo.length());
        recvAckInfo();
    }
    else
    {
        QByteArray b;
        b = regInfo.toLatin1();
        memcpy(regmsg,b.data(),regInfo.length());
        qDebug()<<"[recvClient]: regmsg: "<<regmsg<<endl;
        qDebug()<<"[recvClient]: len of regmsg: "<<strlen(regmsg)<<endl;
        dePack();
//        if((regmsg[0] == 'L') && (regmsg[1] == 'o') && (regmsg[2] == 'g'))
//        {
//            logInfo = regInfo;
//            memcpy(logMsg,regmsg,strlen(regmsg));
//            logOperation();
//        }
//        else
//        {
//            dePack();
//        }
    }
}

void MainWindow::eidOperation()
{
    QString str;

}



void MainWindow::readClient()
{
    QString str;

    str = clientConn->readAll();
    QMessageBox::about(this,"msg",str);
    cipherT.clear();
    cipherT.append(str);
    //cipherT.append(str.data());
    //saveFile(ui->pFilepath->toPlainText(),plainT);
    //saveFile(ui->cFilepath->toPlainText(),cipherT);
}



void MainWindow::on_listenBtn_clicked()
{
    setListen();
    setLogListen();
    setEidListen();
//    recvClient();
}

void MainWindow::decrypt_RSA()
{
     /*缺少解密过程，暂时使明文等于密文*/
    //plainT.clear();
    //plainT.append(cipherT);

    long long tmp;
    int i=0;
    /*char chp;
    char chc;
    char cht;
    QChar qCht;
    */
    chp=new char[cipherT.length()];
    chc=new char[cipherT.length()];
    cht=new char[cipherT.length()];
    ba=cipherT.toLatin1();
    chc=ba.data();

    for(i=0;i<cipherT.length();i++)
    {
        tmp=pow(chc[i],e2);
        chp[i]=tmp%n;
        NEW_CHAR_DECODE(cht[i],chp[i]);

        /*
        chc = cipherT.at(i).toAscii();
        //tmp = pow(chc,e2);
        //chp = tmp%n;


        //NEW_CHAR_DECODE(chp,chc);
        //qCht.fromAscii(chp);
        qCht.fromAscii(chc);
        plainT.replace(i,1,qCht);
        //plainT.replace()
        */

    }
    plainT=QString(QLatin1String(cht));
    ui->cipherText->clear();
    ui->cipherText->appendPlainText(plainT);
//    saveFile(ui->pFilepath->toPlainText(),plainT);
//    saveFile(ui->cFilepath->toPlainText(),cipherT);
}

void MainWindow::recvhy1()
{
    hyInfo = logInfo;
    qDebug()<<"[recvh1: ]"<<"hyInfo:"<<hyInfo;

    QByteArray b;
    b = hyInfo.toLatin1();
    len_msghy = hyInfo.length()+1;
    msghy = (char *)malloc(len_msghy*sizeof(char));
    memset(msghy,'\0',len_msghy);
    memcpy(msghy,b.data(),len_msghy);

    qDebug()<<"[recvh1: ]"<<"msghy:"<<msghy;

    len_hn02 = 7;
    hn02 = (char *)malloc(len_hn02*sizeof(char));
    memset(hn02,'\0',len_hn02);
    memcpy(hn02,msghy+2,len_hn02-1);

    qDebug()<<"[recvh1: ]"<<"hn02:"<<hn02;

    len_y1 = 7;
    y1 = (char *)malloc(len_y1*sizeof(char));
    memset(y1,'\0',len_y1);
    memcpy(y1,msghy+2+len_hn02-1,len_y1-1);
    qDebug()<<"[recvh1: ]"<<"y1:"<<y1;


}

void MainWindow::recvLog()
{
//    char *type;
    int len_type = 3;
//    type = (char *)malloc(len_type*sizeof(char));
    memset(type,'\0',len_type);

    logInfo = clientLog->readAll();
    QByteArray b;
     b = logInfo.toLatin1();
    memset(logMsg,'\0',len_logmsg);
    memcpy(logMsg,b.data(),logInfo.length());

    memcpy(type,logMsg,2);
    qDebug()<<"[recvLog: ]"<<"logInfo: "<<logInfo;
    qDebug()<<"[recvLog: ]"<<"logMsg: "<<logMsg;
    qDebug()<<"[recvLog: ]"<<"type: "<<type;

    if(type[0] == '0' && type[1] == '1')
    {
        strTime = ctime.currentTime().toString();
//        saveFile(ui->logFilepath->toPlainText(),strTime);
        qDebug()<<"[recvLog: ]"<<"new log @"<<strTime;

        memcpy(n0,logMsg+2,1);
        memcpy(id_tmp,logMsg+3,logInfo.length()-3);
        qDebug()<<"[recvLog: ]"<<"id_tmp: "<<id_tmp<<"n0: "<<n0;
        sendIdList();
    }
    else if(type[0] == '0' && type[1] == '3')
    {
        recvhy1();
//        setEidListen();
    }



}

void MainWindow::processOver()
{
    qDebug()<<"[processOver: ]"<<"ing...";
}

void MainWindow::writeAck()
{
    memset(type,'\0',3);
    type[0] = '0';
    type[1] = '4';

    char ack[] = "y";

    QString ackMsg;
    char *aMsg;
    int len_aMsg;
    len_aMsg = 2+1;

    aMsg = (char *)malloc(len_aMsg*sizeof(char));
    memset(aMsg,'\0',len_aMsg);

    memcpy(aMsg,type,2);
    memcpy(aMsg+2,ack,1);
    ackMsg = QString(QLatin1String(aMsg));
    qDebug()<<"[writeAck: ]"<<"ing...";
    qDebug()<<"[writeAck: ]"<<"ackMsg"<<ackMsg;

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

    char sender[] = "SP";
    char recver[] = "client";

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

    saveFile(LogFilePath,ackMsg);






    int length;
    if((length = clientLog->write(ackMsg.toLatin1(),ackMsg.length())) != ackMsg.length())
    {
        qDebug()<<"[writeAck:]"<<"write ack to client error!";
    }

    char msg[8] = "logged!";
    msg[7] = '\0';
    char *message;
    int len_message = strlen(msg)+strlen(loger->name)+2;
    message = (char *)malloc(len_message*sizeof(char));
    memset(message,'\0',len_message);

    memcpy(message,loger->name,strlen(loger->name));
    message[strlen(loger->name)] = ' ';
    memcpy(message+strlen(loger->name)+1,msg,strlen(msg));
    QString strMsg;
    strMsg = QString(QLatin1String(message));
    ui->cipherText->appendPlainText(strMsg);
    saveFile(ui->logFilepath->toPlainText(),strMsg);


     qDebug()<<"[writeAck: ]"<<"write over.";
     processOver();
}

void MainWindow::sendIdList()
{


    QFile *file = new QFile(ui->dataFilepath->toPlainText());
   // if(!file->open(QIODevice::WriteOnly | QIODevice::Text))

//读取文件 按照id_tmp来找到对应的注册信息，将其赋值给登录者loger
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"[sendIdList :]"<<"open file error!";
    }


    QTextStream txtInput(file);
    QString lineStr;
    QByteArray bStr;
    char *name;
    int len_name=20;
    name = (char *)malloc(len_name*sizeof(char));
    memset(name,'\0',len_name);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("sp_test");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();

    if(!ok) qDebug()<<"open database failed";
    QSqlQuery query;
    query.exec("use sp_test");
    query.exec("select * from reg_test");

    while(query.next()) {
        qDebug()<<"[sendIdList: ]"<<"is now checking username in database...";
        lineStr = query.value(1).toString();
        bStr = lineStr.toLatin1();
        memcpy(name,bStr.data(),lineStr.length());
        qDebug()<<"[sendIdList: ]"<<"lineStr:"<<lineStr;
        qDebug()<<"[sendIdList: ]"<<"name:"<<name;

        if(!strcmp(name,id_tmp))
        {
            memcpy(loger->name,id_tmp,strlen(id_tmp));
            loger->len_name = strlen(id_tmp);

            qDebug()<<"[sendIdList: ]"<<"loger->name"<<loger->name<<"   loger->len_name"<<loger->len_name;

            lineStr = query.value(2).toString();
            bStr = lineStr.toLatin1();
            memcpy(loger->eIDNum,bStr.data(),lineStr.length());
            loger->len_eidnum = lineStr.length();

            qDebug()<<"[sendIdList: ]"<<"loger->eIDNum"<<loger->eIDNum<<"   loger->len_eidnum"<<loger->len_eidnum;

            lineStr = query.value(3).toString();
            bStr = lineStr.toLatin1();
            memcpy(loger->guid,bStr.data(),lineStr.length());
            loger->len_guid = lineStr.length();

            qDebug()<<"[sendIdList: ]"<<"loger->guid"<<loger->guid<<"   loger->len_guid"<<loger->len_guid;

            lineStr = query.value(4).toString();
            bStr = lineStr.toLatin1();
            memcpy(loger->m,bStr.data(),lineStr.length());
            loger->len_m = lineStr.length();

            qDebug()<<"[sendIdList: ]"<<"loger->m"<<loger->m<<"   loger->len_m"<<loger->len_m;

            lineStr = query.value(5).toString();
            bStr = lineStr.toLatin1();
            memcpy(loger->y,bStr.data(),lineStr.length());
            loger->len_y = lineStr.length();

            qDebug()<<"[sendIdList: ]"<<"loger->y"<<loger->y<<"   loger->len_y"<<loger->len_y;

            lineStr = query.value(6).toString();
            bStr = lineStr.toLatin1();
            memcpy(loger->rtime,bStr.data(),lineStr.length());
            loger->len_time = lineStr.length();

            qDebug()<<"[sendIdList: ]"<<"loger->rtime"<<loger->rtime<<"   loger->len_time"<<loger->len_time;

            break;
        }
//        else
//        {
//            memset(name,'\0',len_name);
//            continue;
//        }

    }


//    while(!txtInput.atEnd())
//    {
//        qDebug()<<"[sendIdList: ]"<<"is now checking username in data file...";
//        lineStr = txtInput.readLine();
//        bStr = lineStr.toLatin1();
//        memcpy(name,bStr.data(),lineStr.length());
//        qDebug()<<"[sendIdList: ]"<<"lineStr:"<<lineStr;
//        qDebug()<<"[sendIdList: ]"<<"name:"<<name;

//        if(!strcmp(name,id_tmp))
//        {
//            memcpy(loger->name,id_tmp,strlen(id_tmp));
//            loger->len_name = strlen(id_tmp);

//            qDebug()<<"[sendIdList: ]"<<"loger->name"<<loger->name<<"   loger->len_name"<<loger->len_name;

//            lineStr = txtInput.readLine();
//            bStr = lineStr.toLatin1();
//            memcpy(loger->eIDNum,bStr.data(),lineStr.length());
//            loger->len_eidnum = lineStr.length();

//            qDebug()<<"[sendIdList: ]"<<"loger->eIDNum"<<loger->eIDNum<<"   loger->len_eidnum"<<loger->len_eidnum;

//            lineStr = txtInput.readLine();
//            bStr = lineStr.toLatin1();
//            memcpy(loger->guid,bStr.data(),lineStr.length());
//            loger->len_guid = lineStr.length();

//            qDebug()<<"[sendIdList: ]"<<"loger->guid"<<loger->guid<<"   loger->len_guid"<<loger->len_guid;

//            lineStr = txtInput.readLine();
//            bStr = lineStr.toLatin1();
//            memcpy(loger->m,bStr.data(),lineStr.length());
//            loger->len_m = lineStr.length();

//            qDebug()<<"[sendIdList: ]"<<"loger->m"<<loger->m<<"   loger->len_m"<<loger->len_m;

//            lineStr = txtInput.readLine();
//            bStr = lineStr.toLatin1();
//            memcpy(loger->y,bStr.data(),lineStr.length());
//            loger->len_y = lineStr.length();

//            qDebug()<<"[sendIdList: ]"<<"loger->y"<<loger->y<<"   loger->len_y"<<loger->len_y;

//            lineStr = txtInput.readLine();
//            bStr = lineStr.toLatin1();
//            memcpy(loger->rtime,bStr.data(),lineStr.length());
//            loger->len_time = lineStr.length();

//            qDebug()<<"[sendIdList: ]"<<"loger->rtime"<<loger->rtime<<"   loger->len_time"<<loger->len_time;

//            break;
//        }
//        else
//        {
//            memset(name,'\0',len_name);
//            continue;
//        }

//    }

    file->close();


//    EpubS{[eIDNum,h(n0+1),msgIdInfo,SPcert]<id,Ti,M'>}
//    EpubS(msgIdList);
//    msgIdList = type + loger->eIDNum + h(n0+1) + msgIdInfo + SPcert + msg_idtm;
//    msg_idtm = loger->id + loger->rtime + this->m1;


    char *msg_idtm;  //<ID Ti M'>
    int len_msgidtm;
    len_msgidtm = strlen(loger->name)+loger->len_time+len_m1;
    msg_idtm = (char *)malloc(len_msgidtm*sizeof(char));
    memset(msg_idtm,'\0',len_msgidtm);
    memcpy(msg_idtm,loger->name,strlen(loger->name));
    memcpy(msg_idtm+strlen(loger->name),loger->rtime,loger->len_time-1);
    memcpy(msg_idtm+strlen(loger->name)+loger->len_time-1,m1,len_m1);



    char *msgIdInfo;   //身份请求信息   //拿数字表示 或者拿位表示
    int len_msgIdInfo;
    len_msgIdInfo = 2;
    msgIdInfo = (char *)malloc(len_msgIdInfo*sizeof(char));
    memset(msgIdInfo,'\0',len_msgIdInfo);
    msgIdInfo[0] = 27;   // 0001 1011 意味：性别，身份证号，联系电话，真实姓名

    memset(type,'\0',3);  //消息类型
    type[0] = '0';
    type[1] = '2';

    char *msgIdList;       //最终要传递的消息
    int len_msgIdList;


    char add[2];   //n0要+的1
    add[0] = '1';
    add[1] = '\0';


    len_hn01 = 7;
    hn01 = (char *)malloc(len_hn01*sizeof(char));
    memset(hn01,'\0',len_hn01);
//    memcpy(hn01,msghy+2,len_hn01-1);

    hn01 = hash(n0,1,add,1);
//    loger->y = hash(n0,1,add,1);


    len_msgIdList = 2 + loger->len_eidnum + len_hn01 + len_msgIdInfo + len_SPCert + len_msgidtm;
    msgIdList = (char *)malloc(len_msgIdList*sizeof(char));
    memset(msgIdList,'\0',len_msgIdList);

    memcpy(msgIdList,type,2);
    qDebug()<<"[sendIdList: ]"<<"type:"<<type;

    memcpy(msgIdList+2,loger->eIDNum,8);
    qDebug()<<"[sendIdList: ]"<<"loger->eIDNum:"<<loger->eIDNum;

    memcpy(msgIdList+2+8,hn01,6);
    qDebug()<<"[sendIdList: ]"<<"hn01:"<<hn01;

    memcpy(msgIdList+2+8+6,msgIdInfo,1);
    qDebug()<<"[sendIdList: ]"<<"msgIdInfo:"<<msgIdInfo;

    memcpy(msgIdList+2+8+6+1,SPCert,19);
    qDebug()<<"[sendIdList: ]"<<"SPCert:"<<SPCert;

    memcpy(msgIdList+2+8+6+1+19,msg_idtm,len_msgidtm);
    qDebug()<<"[sendIdList: ]"<<"msg_idtm:"<<msg_idtm;



    QString messageIdList;
    messageIdList = QString(QLatin1String(msgIdList));

    qDebug()<<"[sendIdList: ]"<<"messageIdList:"<<messageIdList;

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

    char sender[] = "SP";
    char recver[] = "client";

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

    saveFile(LogFilePath,messageIdList);


    int length;
    if((length = clientLog->write(messageIdList.toLatin1(),messageIdList.length())) != messageIdList.length())
    {
        qDebug()<<"[sendIdList: ]"<<"clientLog socket write error!";
    }
}

void MainWindow::fMakeK()
{

}

void MainWindow::eidConnection()
{
    clientEID = serverEID->nextPendingConnection();
    connect(clientEID,SIGNAL(disconnected()),clientEID,SLOT(deleteLater()));
    connect(clientEID,SIGNAL(readyRead()),this,SLOT(recvEid()));

}

void MainWindow::logConnection()
{

    clientLog = serverSP->nextPendingConnection();
    connect(clientLog,SIGNAL(disconnected()),clientLog,SLOT(deleteLater()));
    connect(clientLog,SIGNAL(readyRead()),this,SLOT(recvLog()));
}

void MainWindow::recvEid()
{
    qDebug()<<"[recvEid: ]"<<"ing...";

    QString eMsg;
    char *eidmsg;
    int len_eidmsg;
    eMsg = clientEID->readAll();
    len_eidmsg = eMsg.length()+1;
    eidmsg = (char *)malloc(len_eidmsg*sizeof(char));
    memset(eidmsg,'\0',len_eidmsg);
    QByteArray b;
    b = eMsg.toLatin1();
    memcpy(eidmsg,b.data(),eMsg.length());
    qDebug()<<"[recvEid: ]"<<"eMsg: "<<eMsg;
    qDebug()<<"[recvEid: ]"<<"eidmsg: "<<eidmsg;

    char type[3];
    memset(type,'\0',3);
    memcpy(type,eidmsg,2);
    qDebug()<<"[recvEid: ]"<<"type: "<<type;

    if(type[0] == '2' && type[1] == '1')  //eid服务器发来的消息
    {
        char *hn02tmp;
        int len_hn02tmp = 7;
        hn02tmp = (char *)malloc(len_hn02tmp*sizeof(char));
        memset(hn02tmp,'\0',len_hn02tmp);
        memcpy(hn02tmp,eidmsg+2+1,len_hn02tmp-1);
        qDebug()<<"[recvEid: ]"<<"hn02tmp:"<<hn02tmp;
//此处应该是计算新的y1值，然后与接受到的y1值进行比较
//        char *y1tmp;
//        int len_y1tmp = 7;
//        y1tmp = (char *)malloc(len_y1tmp*sizeof(char));
//        y1tmp = hash();
      qDebug()<<"[recvEid: ]"<<"ing... ";

        if(!strcmp(hn02,hn02tmp))
        {
            QString newMsg;
            char *nMsg;
            int len_nMsg;

            char arr[9] = "logged!";
            arr[7] = '\0';
            len_nMsg = strlen(arr) + loger->len_name;
            nMsg = (char *)malloc(len_nMsg*sizeof(char));
            memset(nMsg,'\0',len_nMsg);

            memcpy(nMsg,loger->name,strlen(loger->name));
            memset(nMsg+strlen(loger->name),' ',1);
            memcpy(nMsg+1+strlen(loger->name),arr,strlen(arr));

            newMsg = QString(QLatin1String(nMsg));
            qDebug()<<"[recvEid: ]"<<"strcmp(hn02,hn02tmp)";
            ui->cipherText->appendPlainText(newMsg);
            //在消息区显示新用户登录
            writeAck();
        }
//        eidOperation();
    }
}

//void MainWindow::logOperation()
//{

//}

//char *MainWindow::hash(char *para1,int len_para1,char *para2,int len_para2)
//{
//    char *tmp;
//    int len_tmp;
//    len_tmp = len_para1+len_para2;
//    tmp = (char *)malloc(len_tmp*sizeof(char));
//    memcpy(tmp,para1,len_para1-1);
//    memcpy(tmp+len_para1-1,para2,len_para2-1);
//    /*
//      缺少真实哈希运算
//    */

////    return tmp;
//    return tmp;

//}

char *MainWindow::hash(char *p,int len_p,char *time,int len_time)
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
