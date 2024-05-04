/****************************************************************************
** Meta object code from reading C++ file 'mdp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled3/mdp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mdp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mdp_t {
    QByteArrayData data[8];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mdp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mdp_t qt_meta_stringdata_mdp = {
    {
QT_MOC_LITERAL(0, 0, 3), // "mdp"
QT_MOC_LITERAL(1, 4, 18), // "on_envoyer_clicked"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "sendMail"
QT_MOC_LITERAL(4, 33, 5), // "email"
QT_MOC_LITERAL(5, 39, 8), // "mailSent"
QT_MOC_LITERAL(6, 48, 9), // "sendMaile"
QT_MOC_LITERAL(7, 58, 9) // "mailSente"

    },
    "mdp\0on_envoyer_clicked\0\0sendMail\0email\0"
    "mailSent\0sendMaile\0mailSente"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mdp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    1,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void mdp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mdp *_t = static_cast<mdp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_envoyer_clicked(); break;
        //case 1: _t->sendMail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        //case 2: _t->mailSent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendMaile(); break;
        case 4: _t->mailSente((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject mdp::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mdp.data,
      qt_meta_data_mdp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mdp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mdp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mdp.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int mdp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
