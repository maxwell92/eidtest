#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QStringList"
#include "QMessageBox"
#include "QDebug"
#include "QtSql/QSqlQuery"

//#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
        qDebug()<<"\t"<<driver;
    createConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   // db.setDatabaseName("test1");
    db.setDatabaseName("eid_server_test");
    db.setUserName("root");
    db.setPassword("root");
    bool ok = db.open();

    if(!ok) qDebug()<<"open database failed";

    QSqlQuery query;
    //query.exec("use test1");
    query.exec("use eid_server_test");
    //query.exec("select * from people");
    query.exec("select * from info_test");





    while(query.next()) {
         QString text1 = query.value(0).toString();
         qDebug()<<text1;
         QString text2 = query.value(1).toString();
         qDebug()<<text2;
         QString text3 = query.value(2).toString();
         qDebug()<<text3;
         QString text4 = query.value(3).toString();
         qDebug()<<text4;
         QString text5 = query.value(4).toString();
         qDebug()<<text5;
         QString text6 = query.value(5).toString();
         qDebug()<<text6;
         QString text7 = query.value(6).toString();
         qDebug()<<text7;
         QString text8 = query.value(7).toString();
         qDebug()<<text8;
         QString text9 = query.value(8).toString();
         qDebug()<<text9;
         QString text10 = query.value(9).toString();
         qDebug()<<text10;
    }




//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

//    db.setDatabaseName("test1");
//    db.setUserName("root");
//    db.setPassword("root");
//    bool ok = db.open();
//    if(!ok) {
//    //QMessageBox::critical(0, QObject::tr("connection failed!"), db.lastError().text()); //invalid use of incomplete type "struct QSqlError"
//         QMessageBox::critical(0, QObject::tr("connection failed!"), QObject::tr("Nothing to tell"));
//         return false;
//    } else {
//        QMessageBox::information(0, QObject::tr("Tips"), QObject::tr("connection succeed"));
//        return true;
//    }
//    QSqlQuery query;
////    query.exec("create table info_test");

//    query.exec("use test1");
//    query.exec("select * from test1");
//    qDebug()<<"use & select ";
//    while(query.next()) {
//        QString text1 = query.value(0).toString();
//        qDebug()<<text1;
//        QString text2 = query.value(1).toString();
//        qDebug()<<text2;
//        QString text3 = query.value(2).toString();
//        qDebug()<<text3;
//        QString text4 = query.value(3).toString();
//        qDebug()<<text4;
//    }


//    db.setDatabaseName("test");
//    db.setUserName("root");
//    db.setPassword("root");

//    bool ok = db.open();
////    if(!ok) {
////        //QMessageBox::critical(0, QObject::tr("connection failed!"), db.lastError().text()); //invalid use of incomplete type "struct QSqlError"
////        QMessageBox::critical(0, QObject::tr("connection failed!"), QObject::tr("Nothing to tell"));

////          return false;
////    } else {
////        QMessageBox::information(0, QObject::tr("Tips"), QObject::tr("connection succeed"));
//////        return true;
////    }
////    QSqlQuery query;
////    //query.exec("create table test");
////    query.exec("use test1");

//    query.exec("select * from info_test");




}


