/********************************************************************************
** Form generated from reading UI file 'dlgpin.ui'
**
** Created: Sun Dec 6 17:50:18 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPIN_H
#define UI_DLGPIN_H

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

class Ui_dlgpin
{
public:
    QPushButton *OkBtn;
    QPushButton *CancleBtn;
    QLineEdit *pinE;
    QLabel *label;

    void setupUi(QDialog *dlgpin)
    {
        if (dlgpin->objectName().isEmpty())
            dlgpin->setObjectName(QString::fromUtf8("dlgpin"));
        dlgpin->resize(400, 300);
        OkBtn = new QPushButton(dlgpin);
        OkBtn->setObjectName(QString::fromUtf8("OkBtn"));
        OkBtn->setGeometry(QRect(92, 238, 92, 27));
        CancleBtn = new QPushButton(dlgpin);
        CancleBtn->setObjectName(QString::fromUtf8("CancleBtn"));
        CancleBtn->setGeometry(QRect(212, 238, 92, 27));
        pinE = new QLineEdit(dlgpin);
        pinE->setObjectName(QString::fromUtf8("pinE"));
        pinE->setGeometry(QRect(132, 156, 113, 27));
        label = new QLabel(dlgpin);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(136, 102, 101, 17));

        retranslateUi(dlgpin);

        QMetaObject::connectSlotsByName(dlgpin);
    } // setupUi

    void retranslateUi(QDialog *dlgpin)
    {
        dlgpin->setWindowTitle(QApplication::translate("dlgpin", "eID\351\252\214\350\257\201", 0, QApplication::UnicodeUTF8));
        OkBtn->setText(QApplication::translate("dlgpin", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        CancleBtn->setText(QApplication::translate("dlgpin", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dlgpin", "\350\276\223\345\205\2454\344\275\215PIN", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgpin: public Ui_dlgpin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGPIN_H
