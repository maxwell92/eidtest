/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 27 11:35:03 2015
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
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *encryBtn;
    QPushButton *sendBtn;
    QPlainTextEdit *plainText;
    QPlainTextEdit *addressT;
    QPlainTextEdit *portT;
    QLabel *addressL;
    QLabel *portL;
    QPlainTextEdit *pFilepath;
    QPlainTextEdit *cFilepath;
    QLabel *pFilepathL;
    QLabel *cFilepathT;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(542, 389);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        encryBtn = new QPushButton(centralWidget);
        encryBtn->setObjectName(QString::fromUtf8("encryBtn"));
        encryBtn->setGeometry(QRect(322, 354, 92, 27));
        sendBtn = new QPushButton(centralWidget);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setGeometry(QRect(438, 352, 92, 27));
        plainText = new QPlainTextEdit(centralWidget);
        plainText->setObjectName(QString::fromUtf8("plainText"));
        plainText->setGeometry(QRect(12, 10, 295, 373));
        plainText->setStyleSheet(QString::fromUtf8("font: 14pt \"Abyssinica SIL\";"));
        addressT = new QPlainTextEdit(centralWidget);
        addressT->setObjectName(QString::fromUtf8("addressT"));
        addressT->setGeometry(QRect(362, 30, 167, 29));
        portT = new QPlainTextEdit(centralWidget);
        portT->setObjectName(QString::fromUtf8("portT"));
        portT->setGeometry(QRect(362, 80, 75, 29));
        addressL = new QLabel(centralWidget);
        addressL->setObjectName(QString::fromUtf8("addressL"));
        addressL->setGeometry(QRect(316, 36, 37, 17));
        portL = new QLabel(centralWidget);
        portL->setObjectName(QString::fromUtf8("portL"));
        portL->setGeometry(QRect(316, 88, 37, 17));
        pFilepath = new QPlainTextEdit(centralWidget);
        pFilepath->setObjectName(QString::fromUtf8("pFilepath"));
        pFilepath->setGeometry(QRect(322, 196, 201, 33));
        pFilepath->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        cFilepath = new QPlainTextEdit(centralWidget);
        cFilepath->setObjectName(QString::fromUtf8("cFilepath"));
        cFilepath->setGeometry(QRect(322, 260, 201, 33));
        cFilepath->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        pFilepathL = new QLabel(centralWidget);
        pFilepathL->setObjectName(QString::fromUtf8("pFilepathL"));
        pFilepathL->setGeometry(QRect(322, 172, 125, 17));
        cFilepathT = new QLabel(centralWidget);
        cFilepathT->setObjectName(QString::fromUtf8("cFilepathT"));
        cFilepathT->setGeometry(QRect(324, 238, 125, 17));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "xxx\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        encryBtn->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206", 0, QApplication::UnicodeUTF8));
        sendBtn->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        plainText->setPlainText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\276\205\345\212\240\345\257\206\346\226\207\346\234\254...", 0, QApplication::UnicodeUTF8));
        addressT->setPlainText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        portT->setPlainText(QApplication::translate("MainWindow", "16689", 0, QApplication::UnicodeUTF8));
        addressL->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        portL->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        pFilepath->setPlainText(QApplication::translate("MainWindow", "/home/chen/maxwell/pFile1", 0, QApplication::UnicodeUTF8));
        cFilepath->setPlainText(QApplication::translate("MainWindow", "/home/chen/maxwell/cFile1", 0, QApplication::UnicodeUTF8));
        pFilepathL->setText(QApplication::translate("MainWindow", "\346\230\216\346\226\207\344\277\235\345\255\230\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        cFilepathT->setText(QApplication::translate("MainWindow", "\345\257\206\346\226\207\344\277\235\345\255\230\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
