/****************************************************************************
** Meta object code from reading C++ file 'dialoglinearpointoperation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../include/dialoglinearpointoperation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoglinearpointoperation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogLinearPointOperation_t {
    QByteArrayData data[9];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogLinearPointOperation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogLinearPointOperation_t qt_meta_stringdata_DialogLinearPointOperation = {
    {
QT_MOC_LITERAL(0, 0, 26), // "DialogLinearPointOperation"
QT_MOC_LITERAL(1, 27, 26), // "signalLinearPointOperation"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 34), // "signalLinearPointOperationFin..."
QT_MOC_LITERAL(4, 90, 7), // "QImage&"
QT_MOC_LITERAL(5, 98, 30), // "emitSignalLinearPointOperation"
QT_MOC_LITERAL(6, 129, 14), // "pointOperation"
QT_MOC_LITERAL(7, 144, 7), // "QImage*"
QT_MOC_LITERAL(8, 152, 11) // "originImage"

    },
    "DialogLinearPointOperation\0"
    "signalLinearPointOperation\0\0"
    "signalLinearPointOperationFinished\0"
    "QImage&\0emitSignalLinearPointOperation\0"
    "pointOperation\0QImage*\0originImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogLinearPointOperation[] = {

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
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void DialogLinearPointOperation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogLinearPointOperation *_t = static_cast<DialogLinearPointOperation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLinearPointOperation(); break;
        case 1: _t->signalLinearPointOperationFinished((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->emitSignalLinearPointOperation(); break;
        case 3: _t->pointOperation((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DialogLinearPointOperation::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogLinearPointOperation::signalLinearPointOperation)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogLinearPointOperation::*_t)(QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogLinearPointOperation::signalLinearPointOperationFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogLinearPointOperation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogLinearPointOperation.data,
      qt_meta_data_DialogLinearPointOperation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogLinearPointOperation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogLinearPointOperation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogLinearPointOperation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogLinearPointOperation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DialogLinearPointOperation::signalLinearPointOperation()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DialogLinearPointOperation::signalLinearPointOperationFinished(QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
