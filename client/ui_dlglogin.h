/********************************************************************************
** Form generated from reading UI file 'dlglogin.ui'
**
** Created: Thu Dec 18 08:27:12 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGLOGIN_H
#define UI_DLGLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dlgLogin
{
public:
    QLabel *appLabel;
    QLabel *nameLabel;
    QLineEdit *nameLEdit;
    QPushButton *logBtn;
    QPushButton *regBtn;
    QLabel *pwdLabel_2;
    QLineEdit *pwdLEdit_2;
    QLabel *mLabel_3;
    QLineEdit *mLEdit_3;

    void setupUi(QDialog *dlgLogin)
    {
        if (dlgLogin->objectName().isEmpty())
            dlgLogin->setObjectName(QString::fromUtf8("dlgLogin"));
        dlgLogin->resize(330, 263);
        appLabel = new QLabel(dlgLogin);
        appLabel->setObjectName(QString::fromUtf8("appLabel"));
        appLabel->setGeometry(QRect(100, 20, 87, 17));
        nameLabel = new QLabel(dlgLogin);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(24, 62, 87, 17));
        nameLEdit = new QLineEdit(dlgLogin);
        nameLEdit->setObjectName(QString::fromUtf8("nameLEdit"));
        nameLEdit->setGeometry(QRect(112, 56, 187, 27));
        logBtn = new QPushButton(dlgLogin);
        logBtn->setObjectName(QString::fromUtf8("logBtn"));
        logBtn->setGeometry(QRect(30, 210, 92, 27));
        regBtn = new QPushButton(dlgLogin);
        regBtn->setObjectName(QString::fromUtf8("regBtn"));
        regBtn->setGeometry(QRect(194, 206, 92, 27));
        pwdLabel_2 = new QLabel(dlgLogin);
        pwdLabel_2->setObjectName(QString::fromUtf8("pwdLabel_2"));
        pwdLabel_2->setGeometry(QRect(26, 102, 87, 17));
        pwdLEdit_2 = new QLineEdit(dlgLogin);
        pwdLEdit_2->setObjectName(QString::fromUtf8("pwdLEdit_2"));
        pwdLEdit_2->setGeometry(QRect(114, 96, 187, 27));
        mLabel_3 = new QLabel(dlgLogin);
        mLabel_3->setObjectName(QString::fromUtf8("mLabel_3"));
        mLabel_3->setGeometry(QRect(24, 142, 93, 17));
        mLEdit_3 = new QLineEdit(dlgLogin);
        mLEdit_3->setObjectName(QString::fromUtf8("mLEdit_3"));
        mLEdit_3->setGeometry(QRect(116, 138, 187, 27));

        retranslateUi(dlgLogin);

        QMetaObject::connectSlotsByName(dlgLogin);
    } // setupUi

    void retranslateUi(QDialog *dlgLogin)
    {
        dlgLogin->setWindowTitle(QApplication::translate("dlgLogin", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        appLabel->setText(QApplication::translate("dlgLogin", "xxx \345\256\242\346\210\267\347\253\257", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("dlgLogin", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        logBtn->setText(QApplication::translate("dlgLogin", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        regBtn->setText(QApplication::translate("dlgLogin", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        pwdLabel_2->setText(QApplication::translate("dlgLogin", "\345\217\243\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        mLabel_3->setText(QApplication::translate("dlgLogin", "\346\263\250\345\206\214\346\227\266\351\232\217\346\234\272\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgLogin: public Ui_dlgLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGLOGIN_H
