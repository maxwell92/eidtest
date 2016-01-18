/********************************************************************************
** Form generated from reading UI file 'dlgreg.ui'
**
** Created: Thu Dec 18 08:27:12 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGREG_H
#define UI_DLGREG_H

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

class Ui_dlgReg
{
public:
    QLabel *regLabel;
    QLabel *nameRLabel;
    QLabel *pRLabel;
    QLabel *eIDRLabel;
    QLabel *mRLabel;
    QPushButton *submitBtn;
    QPushButton *returnBtn;
    QLineEdit *nameRLEdit;
    QLineEdit *pRLEDit;
    QLineEdit *eIDRLEdit;
    QLineEdit *mRLEdit;

    void setupUi(QDialog *dlgReg)
    {
        if (dlgReg->objectName().isEmpty())
            dlgReg->setObjectName(QString::fromUtf8("dlgReg"));
        dlgReg->resize(400, 244);
        regLabel = new QLabel(dlgReg);
        regLabel->setObjectName(QString::fromUtf8("regLabel"));
        regLabel->setGeometry(QRect(164, 20, 62, 17));
        nameRLabel = new QLabel(dlgReg);
        nameRLabel->setObjectName(QString::fromUtf8("nameRLabel"));
        nameRLabel->setGeometry(QRect(46, 58, 62, 17));
        pRLabel = new QLabel(dlgReg);
        pRLabel->setObjectName(QString::fromUtf8("pRLabel"));
        pRLabel->setGeometry(QRect(36, 88, 62, 17));
        eIDRLabel = new QLabel(dlgReg);
        eIDRLabel->setObjectName(QString::fromUtf8("eIDRLabel"));
        eIDRLabel->setGeometry(QRect(42, 120, 62, 17));
        mRLabel = new QLabel(dlgReg);
        mRLabel->setObjectName(QString::fromUtf8("mRLabel"));
        mRLabel->setGeometry(QRect(42, 150, 62, 17));
        submitBtn = new QPushButton(dlgReg);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));
        submitBtn->setGeometry(QRect(68, 190, 92, 27));
        returnBtn = new QPushButton(dlgReg);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));
        returnBtn->setGeometry(QRect(202, 188, 92, 27));
        nameRLEdit = new QLineEdit(dlgReg);
        nameRLEdit->setObjectName(QString::fromUtf8("nameRLEdit"));
        nameRLEdit->setGeometry(QRect(104, 50, 177, 27));
        pRLEDit = new QLineEdit(dlgReg);
        pRLEDit->setObjectName(QString::fromUtf8("pRLEDit"));
        pRLEDit->setGeometry(QRect(104, 82, 177, 27));
        eIDRLEdit = new QLineEdit(dlgReg);
        eIDRLEdit->setObjectName(QString::fromUtf8("eIDRLEdit"));
        eIDRLEdit->setGeometry(QRect(108, 112, 177, 27));
        mRLEdit = new QLineEdit(dlgReg);
        mRLEdit->setObjectName(QString::fromUtf8("mRLEdit"));
        mRLEdit->setGeometry(QRect(108, 142, 177, 27));

        retranslateUi(dlgReg);

        QMetaObject::connectSlotsByName(dlgReg);
    } // setupUi

    void retranslateUi(QDialog *dlgReg)
    {
        dlgReg->setWindowTitle(QApplication::translate("dlgReg", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        regLabel->setText(QApplication::translate("dlgReg", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        nameRLabel->setText(QApplication::translate("dlgReg", "\347\224\250\346\210\267\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        pRLabel->setText(QApplication::translate("dlgReg", "\345\256\211\345\205\250\345\217\243\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        eIDRLabel->setText(QApplication::translate("dlgReg", "eID\345\215\241\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        mRLabel->setText(QApplication::translate("dlgReg", "\351\232\217\346\234\272\346\225\260M\357\274\232", 0, QApplication::UnicodeUTF8));
        submitBtn->setText(QApplication::translate("dlgReg", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        returnBtn->setText(QApplication::translate("dlgReg", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgReg: public Ui_dlgReg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGREG_H
