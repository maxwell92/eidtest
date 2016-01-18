/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Dec 6 17:50:18 2015
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
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCheckBox *nameChk;
    QCheckBox *idChk;
    QCheckBox *teleChk;
    QCheckBox *depChk;
    QCheckBox *ageChk;
    QCheckBox *genChk;
    QCheckBox *insChk;
    QCheckBox *addrChk;
    QPushButton *submitBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(461, 379);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        nameChk = new QCheckBox(centralWidget);
        nameChk->setObjectName(QString::fromUtf8("nameChk"));
        nameChk->setGeometry(QRect(64, 76, 93, 22));
        nameChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        idChk = new QCheckBox(centralWidget);
        idChk->setObjectName(QString::fromUtf8("idChk"));
        idChk->setGeometry(QRect(220, 124, 93, 22));
        idChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        teleChk = new QCheckBox(centralWidget);
        teleChk->setObjectName(QString::fromUtf8("teleChk"));
        teleChk->setGeometry(QRect(220, 72, 93, 22));
        teleChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        depChk = new QCheckBox(centralWidget);
        depChk->setObjectName(QString::fromUtf8("depChk"));
        depChk->setGeometry(QRect(216, 224, 93, 22));
        depChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        ageChk = new QCheckBox(centralWidget);
        ageChk->setObjectName(QString::fromUtf8("ageChk"));
        ageChk->setGeometry(QRect(62, 226, 93, 22));
        ageChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        genChk = new QCheckBox(centralWidget);
        genChk->setObjectName(QString::fromUtf8("genChk"));
        genChk->setGeometry(QRect(62, 172, 93, 22));
        genChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        insChk = new QCheckBox(centralWidget);
        insChk->setObjectName(QString::fromUtf8("insChk"));
        insChk->setGeometry(QRect(218, 176, 93, 22));
        insChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        addrChk = new QCheckBox(centralWidget);
        addrChk->setObjectName(QString::fromUtf8("addrChk"));
        addrChk->setGeometry(QRect(64, 124, 93, 22));
        addrChk->setStyleSheet(QString::fromUtf8("font: 12pt \"Abyssinica SIL\";"));
        submitBtn = new QPushButton(centralWidget);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));
        submitBtn->setGeometry(QRect(162, 328, 92, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "eID\345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        nameChk->setText(QApplication::translate("MainWindow", "\347\234\237\345\256\236\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        idChk->setText(QApplication::translate("MainWindow", "\350\272\253\344\273\275\350\257\201\345\217\267", 0, QApplication::UnicodeUTF8));
        teleChk->setText(QApplication::translate("MainWindow", "\350\201\224\347\263\273\347\224\265\350\257\235", 0, QApplication::UnicodeUTF8));
        depChk->setText(QApplication::translate("MainWindow", "\345\267\245\344\275\234\345\215\225\344\275\215", 0, QApplication::UnicodeUTF8));
        ageChk->setText(QApplication::translate("MainWindow", "\345\271\264\351\276\204", 0, QApplication::UnicodeUTF8));
        genChk->setText(QApplication::translate("MainWindow", "\346\200\247\345\210\253", 0, QApplication::UnicodeUTF8));
        insChk->setText(QApplication::translate("MainWindow", "\347\244\276\344\277\235\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        addrChk->setText(QApplication::translate("MainWindow", "\345\256\266\345\272\255\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        submitBtn->setText(QApplication::translate("MainWindow", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
