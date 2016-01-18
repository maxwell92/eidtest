#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QFile>

#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    clientSP = new QTcpSocket;
    people = new citizen();

    int len_msg = 105;
    msg = (char *)malloc(len_msg*sizeof(char));
    memset(msg,'\0',len_msg);

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




    connect(server,SIGNAL(newConnection()),this,SLOT(newClientConn()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConn()
{
    client = server->nextPendingConnection();

    connect(client,SIGNAL(disconnected()),client,SLOT(deleteLater()));

    connect(client,SIGNAL(readyRead()),this,SLOT(recvClient()));

}

void MainWindow::setListen()
{
    qDebug()<<"[setListen]: "<<"14500";
    if(!server->isListening())
    {
        if(!server->listen(QHostAddress::Any,14500))
        {
            QMessageBox::about(this,"Attention!","listening....");

        }
    }
}

void MainWindow::connSP()
{
    clientSP->connectToHost(QHostAddress::LocalHost,10500);
    qDebug()<<"[connSP: ]"<<"ing...";
    char ack[2];
    ack[0] = '1';
    ack[1] = '\0';

    char type[3];
    type[0] = '2';
    type[1] = '1';
    type[2] = '\0';

    len_spmsg = 9;
    spmsg = (char *)malloc(len_spmsg*sizeof(char));
    memset(spmsg,'\0',len_spmsg);

    memcpy(spmsg,type,2);
    memcpy(spmsg+2,ack,1);
    memcpy(spmsg+3,hn02,len_hn02-1);

    qDebug()<<"[connSP:]"<<"spmsg: "<<spmsg;

    spInfo = QString(QLatin1String(spmsg));

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

    char sender[] = "eidServer";
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

    saveFile(LogFilePath,spInfo);




    int length;
    qDebug()<<"[connSP:]"<<"spInfo: "<<spInfo;
    if((length = clientSP->write(spInfo.toLatin1(),spInfo.length())) != spInfo.length())
    {
        qDebug()<<"[connSP: ]"<<"write error!";
    }
    qDebug()<<"[connSP:]"<<"write over";
    clientSP->close();
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


void MainWindow::recvClient()
{
    qDebug()<<"[recvClient: ]"<<"ing...";
    clientInfo = client->readAll();

    QByteArray b;
    b = clientInfo.toLatin1();

    len_clientmsg = clientInfo.length()+1;
    clientmsg = (char *)malloc(len_clientmsg*sizeof(char));
    memset(clientmsg,'\0',len_clientmsg);
    memcpy(clientmsg,b.data(),len_clientmsg);
    qDebug()<<"[recvClient: ]"<<"clientmsg: "<<clientmsg;

    len_hn02 = 7;
    hn02 = (char *)malloc(len_hn02*sizeof(char));
    memset(hn02,'\0',len_hn02);
    memset(chk,'\0',9);

    len_spcert = 20;
    SPCert = (char *)malloc(len_spcert*sizeof(char));
    memset(SPCert,'\0',len_spcert);

//    int len;
//    len = clientInfo.length()-8-8-len_hn02-1;
//    len_spcert = len;

    int len_msg_now;
    len_msg_now = clientInfo.length()-8-8-6-19;


    memcpy(chk,clientmsg,8);
    memcpy(msg,clientmsg+8,len_msg_now);
    memcpy(people->eIDNum,clientmsg+8+len_msg_now,8);
    memcpy(hn02,clientmsg+16+len_msg_now,len_hn02-1);
    memcpy(SPCert,clientmsg+16+len_msg_now+len_hn02-1,len_spcert-1);

    qDebug()<<"[recvClient: ]"<<"chk: "<<chk;
    qDebug()<<"[recvClient: ]"<<"msg: "<<msg;
    qDebug()<<"[recvClient: ]"<<"eidnum: "<<people->eIDNum;
    qDebug()<<"[recvClient: ]"<<"hn02: "<<hn02;
    qDebug()<<"[recvClient: ]"<<"SPCert: "<<SPCert;

    QString filename;
    char *fname = "/home/chen/maxwell/eidserver.data";
    filename = QString(QLatin1String(fname));
    QFile *file = new QFile(filename);

    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"[recvClient :]"<<"open file error!";
    }

    char *eidtmp;
    eidtmp = (char *)malloc(9*sizeof(char));
    memset(eidtmp,'\0',9);

    int len[8] = {0};

    QTextStream txtInput(file);
    QString lineStr;
    QByteArray bStr;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("eid_server_test");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();

    if(!ok) qDebug()<<"open database failed";
    QSqlQuery query;
    query.exec("use eid_server_test");
    query.exec("select * from info_test");
    while(query.next()) {
        qDebug()<<"[recvClient: ]"<<"is now checking username in database...";
        lineStr = query.value(1).toString();   //lineStr now only mean eidnum
        bStr = lineStr.toLatin1();
        memcpy(eidtmp, bStr.data(), lineStr.length());
        if(!strcmp(eidtmp, people->eIDNum)) {
            lineStr = query.value(2).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->age, bStr.data(), lineStr.length());
            len[0] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"age: "<<people->age;


            lineStr = query.value(3).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->dep,bStr.data(),lineStr.length());
            len[1] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"dep:"<<people->dep;


            lineStr = query.value(4).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->ins,bStr.data(),lineStr.length());
            len[2] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"ins:"<<people->ins;


            lineStr = query.value(5).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->gen,bStr.data(),lineStr.length());
            len[3] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"gen:"<<people->gen;


            lineStr = query.value(6).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->idnum,bStr.data(),lineStr.length());
            len[4] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"idnum:"<<people->idnum;


            lineStr = query.value(7).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->addr,bStr.data(),lineStr.length());
            len[5] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"addr:"<<people->addr;


            lineStr = query.value(8).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->tele,bStr.data(),lineStr.length());
            len[6] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"tele:"<<people->tele;


            lineStr = query.value(9).toString();
            bStr = lineStr.toLatin1();
            memcpy(people->name,bStr.data(),lineStr.length());
            len[7] = lineStr.length();
            qDebug()<<"[recvClient: ]"<<"name:"<<people->name;

            break;
        }

    }

//    while(!txtInput.atEnd())
//    {
//         qDebug()<<"[recvClient: ]"<<"is now checking username in data file...";
//         lineStr = txtInput.readLine();
//         bStr = lineStr.toLatin1();
//         memcpy(eidtmp,bStr.data(),lineStr.length());

//         if(!strcmp(eidtmp,people->eIDNum))
//         {
//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->age,bStr.data(),lineStr.length());
//             len[0] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"age:"<<people->age;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->dep,bStr.data(),lineStr.length());
//             len[1] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"dep:"<<people->dep;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->ins,bStr.data(),lineStr.length());
//             len[2] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"ins:"<<people->ins;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->gen,bStr.data(),lineStr.length());
//             len[3] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"gen:"<<people->gen;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->idnum,bStr.data(),lineStr.length());
//             len[4] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"idnum:"<<people->idnum;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->addr,bStr.data(),lineStr.length());
//             len[5] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"addr:"<<people->addr;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->tele,bStr.data(),lineStr.length());
//             len[6] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"tele:"<<people->tele;


//             lineStr = txtInput.readLine();
//             bStr = lineStr.toLatin1();
//             memcpy(people->name,bStr.data(),lineStr.length());
//             len[7] = lineStr.length();
//             qDebug()<<"[recvClient: ]"<<"name:"<<people->name;

//             break;
//         }
//         else
//         {
//             memset(eidtmp,'\0',9);
//             continue;
//         }
//    }


    char *msg_tmp;
    msg_tmp = (char *)malloc(len_msg*sizeof(char));
    memset(msg_tmp,'\0',len_msg);


    int len_msg_tmp=0;
    int i;
    for(i=0;i<8;i++)
    {
         if(chk[i] == '1' && i==0)
         {
             memcpy(msg_tmp+len_msg_tmp,people->age,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==1)
         {
             memcpy(msg_tmp+len_msg_tmp,people->dep,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==2)
         {
             memcpy(msg_tmp+len_msg_tmp,people->ins,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==3)
         {
             memcpy(msg_tmp+len_msg_tmp,people->gen,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==4)
         {
             memcpy(msg_tmp+len_msg_tmp,people->idnum,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==5)
         {
             memcpy(msg_tmp+len_msg_tmp,people->addr,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==6)
         {
             memcpy(msg_tmp+len_msg_tmp,people->tele,len[i]);
             len_msg_tmp+=len[i];
         }
         if(chk[i] == '1' && i==7)
         {
             memcpy(msg_tmp+len_msg_tmp,people->name,len[i]);
             len_msg_tmp+=len[i];
         }
    }
    qDebug()<<"[recvClient: ]"<<"recv over";
    qDebug()<<"[recvClient: ]"<<"msg_tmp"<<msg_tmp;
    qDebug()<<"[recvClient: ]"<<"msg"<<msg;

//    if(!strcmp(msg_tmp,msg))
//    {

        char mesg[40];
        char m[] = " ask for info";
        memset(mesg,'\0',30);
        memcpy(mesg,people->name,len[7]);
        memcpy(mesg+len[7],m,strlen(m));
        qDebug()<<"[recvClient: ]"<<"mesg:"<<mesg;
        QString mg;
        mg = QString(QLatin1String(mesg));
        ui->msgE->appendPlainText(mg);

        connSP();


//    }



}
void MainWindow::on_startBtn_clicked()
{
    setListen();


}
