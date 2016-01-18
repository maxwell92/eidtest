/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 27 15:57:27 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *msgE;
    QPushButton *startBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 358);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        msgE = new QPlainTextEdit(centralWidget);
        msgE->setObjectName(QString::fromUtf8("msgE"));
        msgE->setGeometry(QRect(46, 22, 301, 249));
        msgE->setStyleSheet(QString::fromUtf8("font: 14pt \"Abyssinica SIL\";"));
        startBtn = new QPushButton(centralWidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setGeometry(QRect(156, 304, 92, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "eID\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        msgE->setPlainText(QApplication::translate("MainWindow", "\350\277\231\351\207\214\346\230\276\347\244\272\346\234\215\345\212\241\345\231\250\346\266\210\346\201\257\357\274\232", 0, QApplication::UnicodeUTF8));
        startBtn->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
