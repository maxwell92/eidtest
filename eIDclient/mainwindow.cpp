#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dlgpin.h>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <malloc.h>
#include <QFile>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dlgPIN = new dlgpin();

    server = new QTcpServer(this);
    eidConn = new QTcpSocket;



    int len_age = 3;
    age = (char *)malloc(len_age*sizeof(char));
    memset(age,'\0',len_age);

    int len_dep = 21;
    dep = (char *)malloc(len_dep*sizeof(char));
    memset(dep,'\0',len_dep);

    int len_ins = 11;
    ins = (char *)malloc(len_ins*sizeof(char));
    memset(ins,'\0',len_ins);

    int len_gen = 2;
    gen = (char *)malloc(len_gen*sizeof(char));
    memset(gen,'\0',len_gen);

    int len_idnum = 19;
    idnum = (char *)malloc(len_idnum*sizeof(char));
    memset(idnum,'\0',len_idnum);

    int len_addr = 21;
    addr = (char *)malloc(len_addr*sizeof(char));
    memset(addr,'\0',len_addr);

    int len_tele = 14;
    tele = (char *)malloc(len_tele*sizeof(char));
    memset(tele,'\0',len_tele);

    int len_name = 21;
    name = (char *)malloc(len_name*sizeof(char));
    memset(name,'\0',len_name);


//    setListen();
    connect(dlgPIN,SIGNAL(showMain()),this,SLOT(showWindow()));
    enterPin();
    connect(server,SIGNAL(newConnection()),this,SLOT(newConn()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConn()
{
    client = server->nextPendingConnection();

    connect(client,SIGNAL(disconnected()),client,SLOT(deleteLater()));
    connect(client,SIGNAL(readyRead()),this,SLOT(recvClnt()));
    qDebug()<<"[newConn: ]"<<"maybe new connection.";
//    if(connect(client,SIGNAL(readyRead()),this,SLOT(recvClient())))
//     {
//        qDebug()<<"[newConn: ]"<<"this is newConn()";
//    }
//    else {
//        qDebug()<<"[newConn: ]"<<"Connection must be wrong.";
//    }
}

void MainWindow::setListen()
{
    qDebug()<<"[setListen: ]"<<"set listening";

    if(!server->isListening())
    {
         if(!server->listen(QHostAddress::Any,13500))
        //if(!server->listen(QHostAddress::LocalHost,13500))
        {
            QMessageBox::about(this,"Attention!","正在监听！");
        }
    }
}

void MainWindow::saveFile(QString filepath, QString str)
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

void MainWindow::connEIDServer()
{
    qDebug()<<"[connEIDServer: ]"<<"ing...";

    eidConn->connectToHost(QHostAddress::LocalHost,14500);


    char *msg;
    int len_msg = 105;
    msg = (char *)malloc(len_msg*sizeof(char));
    memset(msg,'\0',len_msg);



//    len_eidmsg = 8+8+len_hn02-1+len_spcert;
    len_eidmsg = len_msg+8+len_hn02-1+len_spcert;
    eidMsg = (char *)malloc(len_eidmsg*sizeof(char));
    memset(eidMsg,'\0',len_eidmsg);

    char chk[9];
    memset(chk,'\0',9);

    chk[0] = ui->ageChk->isChecked()?'1':'0';
    chk[1] = ui->depChk->isChecked()?'1':'0';
    chk[2] = ui->insChk->isChecked()?'1':'0';
    chk[3] = ui->genChk->isChecked()?'1':'0';
    chk[4] = ui->idChk->isChecked()?'1':'0';
    chk[5] = ui->addrChk->isChecked()?'1':'0';
    chk[6] = ui->teleChk->isChecked()?'1':'0';
    chk[7] = ui->nameChk->isChecked()?'1':'0';



    int len[8]={0};

    char eIDNum[9]="12345678";  //理论上应该由读卡器读入
    eIDNum[8] = '\0';



////    memcpy(eidMsg,chk,8);
//    QString filename;
//    char *fname = "/home/chen/maxwell/eidclient.data";
//    filename = QString(QLatin1String(fname));

//    QFile *file = new QFile(filename);

//    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug()<<"[connEIDServer :]"<<"open file error!";
//    }
//    char *eidtmp;
//    eidtmp = (char *)malloc(9*sizeof(char));
//    memset(eidtmp,'\0',9);

//    QTextStream txtInput(file);
//    QString lineStr;
//    QByteArray bStr;

//    while(!txtInput.atEnd())
//    {
//         qDebug()<<"[connEIDServer: ]"<<"is now checking username in data file...";
//         lineStr = txtInput.readLine();
//         bStr = lineStr.toLatin1();
//         memcpy(eidtmp,bStr.data(),lineStr.length());
//         qDebug()<<"[connEIDServer: ]"<<"eidtmp: "<<eidtmp;
//         qDebug()<<"[connEIDServer: ]"<<"eIDNum: "<<eIDNum;
//         if(!strcmp(eidtmp,eIDNum))
//         {
//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(age,bStr.data(),lineStr.length());
//             len[0] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"age:"<<age;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(dep,bStr.data(),lineStr.length());
//             len[1] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"dep:"<<dep;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(ins,bStr.data(),lineStr.length());
//             len[2] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"ins:"<<ins;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(gen,bStr.data(),lineStr.length());
//             len[3] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"gen:"<<gen;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(idnum,bStr.data(),lineStr.length());
//             len[4] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"idnum:"<<idnum;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(addr,bStr.data(),lineStr.length());
//             len[5] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"addr:"<<addr;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(tele,bStr.data(),lineStr.length());
//             len[6] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"tele:"<<tele;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(name,bStr.data(),lineStr.length());
//             len[7] = lineStr.length();
//             qDebug()<<"[connEIDServer: ]"<<"name:"<<name;

//             break;
//         }
//         else
//         {
//             memset(eidtmp,'\0',9);
//             continue;
//         }
//    }

    int len_msg_now=0;

    int i;
    for(i=0;i<8;i++)
    {
        if(chk[i] == '1' && i==0)
        {
            memcpy(msg+len_msg_now,age,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==1)
        {
            memcpy(msg+len_msg_now,dep,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==2)
        {
            memcpy(msg+len_msg_now,ins,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==3)
        {
            memcpy(msg+len_msg_now,gen,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==4)
        {
            memcpy(msg+len_msg_now,idnum,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==5)
        {
            memcpy(msg+len_msg_now,addr,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==6)
        {
            memcpy(msg+len_msg_now,tele,len[i]);
            len_msg_now+=len[i];
        }
        if(chk[i] == '1' && i==7)
        {
            memcpy(msg+len_msg_now,name,len[i]);
            len_msg_now+=len[i];
        }
    }

//    memcpy(msg,age,len[0]);
//    memcpy(msg+len[0],dep,len[1]);
//    memcpy(msg+len[0]+len[1],ins,len[2]);
//    memcpy(msg+len[0]+len[1]+len[2],gen,len[3]);
//    memcpy(msg+len[0]+len[1]+len[2]+len[3],idnum,len[4]);
//    memcpy(msg+len[0]+len[1]+len[2]+len[3]+len[4],addr,len[5]);
//    memcpy(msg+len[0]+len[1]+len[2]+len[3]+len[4]+len[5],tele,len[6]);
//    memcpy(msg+len[0]+len[1]+len[2]+len[3]+len[4]+len[5]+len[6],name,len[7]);
//    int len_msg_now;
//    len_msg_now = len[0]+len[1]+len[2]+len[3]+len[4]+len[5]+len[6]+len[7];

    qDebug()<<"[connEIDServer: ]"<<"chk: "<<chk;
    qDebug()<<"[connEIDServer: ]"<<"msg: "<<msg;

    memcpy(eidMsg,chk,8);
    qDebug()<<"[connEIDServer: ]"<<"SERVER: "<<eidMsg;

    memcpy(eidMsg+8,msg,len_msg_now);

    qDebug()<<"[connEIDServer: ]"<<"SERVER: "<<eidMsg;
    memcpy(eidMsg+8+len_msg_now,eIDNum,8);

    qDebug()<<"[connEIDServer: ]"<<"SERVER: "<<eidMsg;

    memcpy(eidMsg+8+len_msg_now+8,hn02,len_hn02-1);

    qDebug()<<"[connEIDServer: ]"<<"SERVER: "<<eidMsg;

    qDebug()<<"[connEIDServer: "<<"SPCert: "<<SPCert;

    memcpy(eidMsg+8+len_msg_now+8+len_hn02-1,SPCert,len_spcert-1);   ///PROBLEM
    memcpy(eidMsg+8+len_msg_now+8+len_hn02-1,SPCert,len_spcert);

    qDebug()<<"[connEIDServer: ]"<<"SERVER: "<<eidMsg;

    /////////////////////////////////////////////////////////////////////////////////////

    qDebug()<<"[connEIDServer: ]"<<"eidMsg: "<<eidMsg;
    eidInfo = QString(QLatin1String(eidMsg));
    qDebug()<<"[connEIDServer: ]"<<"eidInfo: "<<eidInfo;

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

    char sender[] = "eidClient";
    char recver[] = "eidServer";

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

    saveFile(LogFilePath,eidInfo);

    int length;
    if((length = eidConn->write(eidInfo.toLatin1(),eidInfo.length())) != eidInfo.length())
    {
        qDebug()<<"[connEIDServer: ]"<<"write eid error";
    }
      qDebug()<<"[connEIDServer: ]"<<"write over";
}

void MainWindow::recvClnt()
{
    char type[3];
    memset(type,'\0',3);



    clientInfo = client->readAll();
    len_clientmsg = clientInfo.length()+1;


    clientmsg = (char *)malloc(len_clientmsg*sizeof(char));
    memset(clientmsg,'\0',len_clientmsg);

    QByteArray b;
    b = clientInfo.toLatin1();
    memcpy(clientmsg,b.data(),len_clientmsg);

    qDebug()<<"[recvClnt: ]"<<"clientInfo: "<<clientInfo;
    qDebug()<<"[recvClnt: ]"<<"clientmsg: "<<clientmsg;

    memcpy(type,clientmsg,2);
    qDebug()<<"[recvClnt: ]"<<"type: "<<type;
    if(type[0] == '1' && type[1] == '0')
    {
        len_hn02 = 7;
        hn02 = (char *)malloc(len_hn02*sizeof(char));
        memset(hn02,'\0',len_hn02);
        len_spcert = 20;
        SPCert = (char *)malloc(len_spcert*sizeof(char));
        memset(SPCert,'\0',len_spcert);

//        int len;
//        len = clientInfo.length()-2-len_hn02-1;
//        len_spcert = len;

        memcpy(SPCert,clientmsg+2,len_spcert-1);
        qDebug()<<"[recvClient: ]"<<"SPCert: "<<SPCert;
        memcpy(hn02,clientmsg+2+len_spcert-1,len_hn02-1);
        qDebug()<<"[recvClient: ]"<<"hn02: "<<hn02;

        wndFlg = 1;

    }


}

void MainWindow::showWindow()
{

   this->setListen();
    this->show();
}

void MainWindow::enterPin()
{
    dlgPIN->show();

}

void MainWindow::on_submitBtn_clicked()
{
//    qDebug()<<strlen(SPCert);
//    qDebug()<<"[on_sumbmitBit_clicked:]"<<strlen(SPCert);
    if(strlen(SPCert) != 0)
    {
        connEIDServer();
    }
//    this->destroy();
}
