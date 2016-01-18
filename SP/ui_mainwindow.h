/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 27 15:57:33 2015
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
    QPlainTextEdit *cipherText;
    QPlainTextEdit *addressT;
    QPlainTextEdit *logFilepath;
    QPlainTextEdit *dataFilepath;
    QLabel *logFilepathL;
    QLabel *addressL;
    QLabel *dataFilepathT;
    QPushButton *listenBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(530, 395);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        cipherText = new QPlainTextEdit(centralWidget);
        cipherText->setObjectName(QString::fromUtf8("cipherText"));
        cipherText->setEnabled(false);
        cipherText->setGeometry(QRect(8, 10, 261, 377));
        cipherText->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Abyssinica SIL\";"));
        addressT = new QPlainTextEdit(centralWidget);
        addressT->setObjectName(QString::fromUtf8("addressT"));
        addressT->setGeometry(QRect(344, 36, 167, 29));
        logFilepath = new QPlainTextEdit(centralWidget);
        logFilepath->setObjectName(QString::fromUtf8("logFilepath"));
        logFilepath->setGeometry(QRect(286, 200, 231, 33));
        logFilepath->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        dataFilepath = new QPlainTextEdit(centralWidget);
        dataFilepath->setObjectName(QString::fromUtf8("dataFilepath"));
        dataFilepath->setGeometry(QRect(288, 264, 229, 33));
        dataFilepath->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        logFilepathL = new QLabel(centralWidget);
        logFilepathL->setObjectName(QString::fromUtf8("logFilepathL"));
        logFilepathL->setGeometry(QRect(306, 176, 125, 17));
        addressL = new QLabel(centralWidget);
        addressL->setObjectName(QString::fromUtf8("addressL"));
        addressL->setGeometry(QRect(300, 40, 37, 17));
        dataFilepathT = new QLabel(centralWidget);
        dataFilepathT->setObjectName(QString::fromUtf8("dataFilepathT"));
        dataFilepathT->setGeometry(QRect(308, 242, 125, 17));
        listenBtn = new QPushButton(centralWidget);
        listenBtn->setObjectName(QString::fromUtf8("listenBtn"));
        listenBtn->setGeometry(QRect(410, 340, 92, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SP", 0, QApplication::UnicodeUTF8));
        cipherText->setPlainText(QApplication::translate("MainWindow", "\346\255\244\345\244\204\345\260\206\346\230\276\347\244\272\347\263\273\347\273\237\350\277\220\350\241\214\345\220\204\347\247\215\346\266\210\346\201\257", 0, QApplication::UnicodeUTF8));
        addressT->setPlainText(QApplication::translate("MainWindow", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        logFilepath->setPlainText(QApplication::translate("MainWindow", "/home/chen/maxwell/sp.log", 0, QApplication::UnicodeUTF8));
        dataFilepath->setPlainText(QApplication::translate("MainWindow", "/home/chen/maxwell/sp.data", 0, QApplication::UnicodeUTF8));
        logFilepathL->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227\344\277\235\345\255\230\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        addressL->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        dataFilepathT->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\277\235\345\255\230\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        listenBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
