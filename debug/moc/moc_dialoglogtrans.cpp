/****************************************************************************
** Meta object code from reading C++ file 'dialoglogtrans.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/dialoglogtrans.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoglogtrans.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogLogTrans_t {
    QByteArrayData data[11];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogLogTrans_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogLogTrans_t qt_meta_stringdata_DialogLogTrans = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DialogLogTrans"
QT_MOC_LITERAL(1, 15, 19), // "signalLogTransStart"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 17), // "signalLogTransEnd"
QT_MOC_LITERAL(4, 54, 7), // "QImage&"
QT_MOC_LITERAL(5, 62, 33), // "on_doubleSpinBoxArgA_valueCha..."
QT_MOC_LITERAL(6, 96, 3), // "arg"
QT_MOC_LITERAL(7, 100, 23), // "emitSignalLogTransStart"
QT_MOC_LITERAL(8, 124, 8), // "logTrans"
QT_MOC_LITERAL(9, 133, 7), // "QImage*"
QT_MOC_LITERAL(10, 141, 11) // "originImage"

    },
    "DialogLogTrans\0signalLogTransStart\0\0"
    "signalLogTransEnd\0QImage&\0"
    "on_doubleSpinBoxArgA_valueChanged\0arg\0"
    "emitSignalLogTransStart\0logTrans\0"
    "QImage*\0originImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogLogTrans[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    1,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void DialogLogTrans::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogLogTrans *_t = static_cast<DialogLogTrans *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLogTransStart(); break;
        case 1: _t->signalLogTransEnd((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->on_doubleSpinBoxArgA_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->emitSignalLogTransStart(); break;
        case 4: _t->logTrans((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DialogLogTrans::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogLogTrans::signalLogTransStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogLogTrans::*_t)(QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogLogTrans::signalLogTransEnd)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogLogTrans::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogLogTrans.data,
      qt_meta_data_DialogLogTrans,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogLogTrans::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogLogTrans::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogLogTrans.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogLogTrans::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void DialogLogTrans::signalLogTransStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DialogLogTrans::signalLogTransEnd(QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
