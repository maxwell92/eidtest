/****************************************************************************
** Meta object code from reading C++ file 'dlgreg.h'
**
** Created: Thu Dec 18 16:36:30 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dlgreg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlgreg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dlgReg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      20,    7,    7,    7, 0x08,
      43,    7,    7,    7, 0x08,
      66,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_dlgReg[] = {
    "dlgReg\0\0showLogin()\0on_submitBtn_clicked()\0"
    "on_returnBtn_clicked()\0recvVeriInfo()\0"
};

void dlgReg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        dlgReg *_t = static_cast<dlgReg *>(_o);
        switch (_id) {
        case 0: _t->showLogin(); break;
        case 1: _t->on_submitBtn_clicked(); break;
        case 2: _t->on_returnBtn_clicked(); break;
        case 3: _t->recvVeriInfo(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData dlgReg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject dlgReg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dlgReg,
      qt_meta_data_dlgReg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dlgReg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dlgReg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dlgReg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dlgReg))
        return static_cast<void*>(const_cast< dlgReg*>(this));
    return QDialog::qt_metacast(_clname);
}

int dlgReg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void dlgReg::showLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
