/****************************************************************************
** Meta object code from reading C++ file 'dlglogin.h'
**
** Created: Thu Dec 18 16:47:44 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlglogin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlglogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dlgLogin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      21,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,    9,    9,    9, 0x08,
      51,    9,    9,    9, 0x08,
      71,    9,    9,    9, 0x08,
      80,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_dlgLogin[] = {
    "dlgLogin\0\0showMain()\0showReg()\0"
    "on_logBtn_clicked()\0on_regBtn_clicked()\0"
    "recvSP()\0recvEClient()\0"
};

void dlgLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        dlgLogin *_t = static_cast<dlgLogin *>(_o);
        switch (_id) {
        case 0: _t->showMain(); break;
        case 1: _t->showReg(); break;
        case 2: _t->on_logBtn_clicked(); break;
        case 3: _t->on_regBtn_clicked(); break;
        case 4: _t->recvSP(); break;
        case 5: _t->recvEClient(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData dlgLogin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject dlgLogin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dlgLogin,
      qt_meta_data_dlgLogin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dlgLogin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dlgLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dlgLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dlgLogin))
        return static_cast<void*>(const_cast< dlgLogin*>(this));
    return QDialog::qt_metacast(_clname);
}

int dlgLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void dlgLogin::showMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void dlgLogin::showReg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
