/****************************************************************************
** Meta object code from reading C++ file 'dialognolinearpointoperation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/dialognolinearpointoperation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialognolinearpointoperation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogNolinearPointOperation_t {
    QByteArrayData data[10];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogNolinearPointOperation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogNolinearPointOperation_t qt_meta_stringdata_DialogNolinearPointOperation = {
    {
QT_MOC_LITERAL(0, 0, 28), // "DialogNolinearPointOperation"
QT_MOC_LITERAL(1, 29, 28), // "signalNoLinearPointOperation"
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 35), // "signalNoLinearPointOperationF..."
QT_MOC_LITERAL(4, 95, 7), // "QImage&"
QT_MOC_LITERAL(5, 103, 32), // "emitSignalNolinearPointOperation"
QT_MOC_LITERAL(6, 136, 19), // "transformTypeSwitch"
QT_MOC_LITERAL(7, 156, 13), // "transformType"
QT_MOC_LITERAL(8, 170, 7), // "QImage*"
QT_MOC_LITERAL(9, 178, 11) // "originImage"

    },
    "DialogNolinearPointOperation\0"
    "signalNoLinearPointOperation\0\0"
    "signalNoLinearPointOperationFinshed\0"
    "QImage&\0emitSignalNolinearPointOperation\0"
    "transformTypeSwitch\0transformType\0"
    "QImage*\0originImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogNolinearPointOperation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x08 /* Private */,
       6,    2,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,

       0        // eod
};

void DialogNolinearPointOperation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogNolinearPointOperation *_t = static_cast<DialogNolinearPointOperation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalNoLinearPointOperation(); break;
        case 1: _t->signalNoLinearPointOperationFinshed((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->emitSignalNolinearPointOperation(); break;
        case 3: _t->transformTypeSwitch((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QImage*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DialogNolinearPointOperation::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogNolinearPointOperation::signalNoLinearPointOperation)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogNolinearPointOperation::*_t)(QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogNolinearPointOperation::signalNoLinearPointOperationFinshed)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogNolinearPointOperation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogNolinearPointOperation.data,
      qt_meta_data_DialogNolinearPointOperation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogNolinearPointOperation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogNolinearPointOperation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogNolinearPointOperation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogNolinearPointOperation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DialogNolinearPointOperation::signalNoLinearPointOperation()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DialogNolinearPointOperation::signalNoLinearPointOperationFinshed(QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
