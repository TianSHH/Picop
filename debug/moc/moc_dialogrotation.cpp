/****************************************************************************
** Meta object code from reading C++ file 'dialogrotation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/dialogrotation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogrotation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogRotation_t {
    QByteArrayData data[9];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogRotation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogRotation_t qt_meta_stringdata_DialogRotation = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DialogRotation"
QT_MOC_LITERAL(1, 15, 19), // "signalRotationStart"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 17), // "signalRotationEnd"
QT_MOC_LITERAL(4, 54, 7), // "QImage&"
QT_MOC_LITERAL(5, 62, 21), // "emitSignalRotationEnd"
QT_MOC_LITERAL(6, 84, 6), // "Rotate"
QT_MOC_LITERAL(7, 91, 7), // "QImage*"
QT_MOC_LITERAL(8, 99, 11) // "originImage"

    },
    "DialogRotation\0signalRotationStart\0\0"
    "signalRotationEnd\0QImage&\0"
    "emitSignalRotationEnd\0Rotate\0QImage*\0"
    "originImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogRotation[] = {

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

void DialogRotation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogRotation *_t = static_cast<DialogRotation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRotationStart(); break;
        case 1: _t->signalRotationEnd((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->emitSignalRotationEnd(); break;
        case 3: _t->Rotate((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DialogRotation::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogRotation::signalRotationStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogRotation::*_t)(QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogRotation::signalRotationEnd)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogRotation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogRotation.data,
      qt_meta_data_DialogRotation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogRotation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogRotation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogRotation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogRotation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DialogRotation::signalRotationStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DialogRotation::signalRotationEnd(QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
