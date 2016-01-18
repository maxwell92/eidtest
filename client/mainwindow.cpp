#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpServer>
#include <math.h>

#define NEW_CHAR_ENCODE(ch,nch) {if(ch>='a' && ch<='z') {nch = ch-96;} else if(ch == ' '){nch=27;} else {nch=28;}}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    n=33;
    e1=3;

    logDialog = new dlgLogin(this);
    logDialog->show();
    regDialog = new dlgReg(this);

    connect(logDialog,SIGNAL(showMain()),this,SLOT(onshowMain()));
    connect(logDialog,SIGNAL(showReg()),this,SLOT(onshowReg()));
    connect(regDialog,SIGNAL(showLogin()),this,SLOT(onshowLog()));
    //connect(regDialog,SIGNAL(showLogin()),logDialog,SLOT(onshowLogin()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onshowMain()
{
    this->show();
}

void MainWindow::onshowReg()
{
    regDialog->show();
}

void MainWindow::onshowLog()
{
    logDialog->show();
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

void MainWindow::encrypt_RSA()
{

    cipherT.clear();
    long long tmp;
        int i=0;
        //char chp;
        //char chc;
        //char cht;
        chp=new char[plainT.length()];
        chc=new char[plainT.length()];
        cht=new char[plainT.length()];
        ba=plainT.toLatin1();
        cht=ba.data();
        for(i=0;i<plainT.length();i++)
        {

            NEW_CHAR_ENCODE(cht[i],chp[i]);
            tmp=pow(chp[i],e1);
            chc[i]=tmp%n;

            /*
            NEW_CHAR_ENCODE(plainT.at(i).toAscii(),chp);
            tmp=pow(chp,e1);
            chc=tmp%n;
            cht=plainT.at(i).toAscii();
            //NEW_CHAR_ENCODE(plainT.at(i),chp);
            //NEW_CHAR_ENCODE(cht,chp);
            //tmp=pow(chp,e1);
            //chc=tmp%n;
            //qCht.fromAscii(chc);
            qCht.fromAscii(cht);
            cipherT.replace(i,1,qCht);
            */
        }
    //cipherT.append(plainT);
    cipherT=QString(QLatin1String(chc));
    saveFile(ui->pFilepath->toPlainText(),plainT);
    saveFile(ui->cFilepath->toPlainText(),cipherT);
}

void MainWindow::on_plainText_textChanged()
{
    tmp = ui->plainText->toPlainText();
    plainT.clear();
    plainT.append(tmp);
}

void MainWindow::on_encryBtn_clicked()
{
    encrypt_RSA();

}

void MainWindow::setConn()
{
    quint16 port;
    QString str;

    str = ui->portT->toPlainText();
    port = str.toInt();
    client->connectToHost(QHostAddress(ui->addressT->toPlainText()),port);
    QMessageBox::about(this,"Attention!",str);

}

void MainWindow::on_sendBtn_clicked()
{
    setConn();



    int length=0;
    if((length=client->write(cipherT.toLatin1(),cipherT.length())) != cipherT.length())
    {
        QMessageBox::about(this,"Attention!","Send failed!");
        exit(-1);
    }



}
