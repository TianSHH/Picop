/****************************************************************************
** Meta object code from reading C++ file 'dialogpowertransformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/dialogpowertransformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogpowertransformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogPowerTransformation_t {
    QByteArrayData data[13];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogPowerTransformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogPowerTransformation_t qt_meta_stringdata_DialogPowerTransformation = {
    {
QT_MOC_LITERAL(0, 0, 25), // "DialogPowerTransformation"
QT_MOC_LITERAL(1, 26, 30), // "signalPowerTransformationStart"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 28), // "signalPowerTransformationEnd"
QT_MOC_LITERAL(4, 87, 7), // "QImage&"
QT_MOC_LITERAL(5, 95, 33), // "on_doubleSpinBoxArgC_valueCha..."
QT_MOC_LITERAL(6, 129, 3), // "arg"
QT_MOC_LITERAL(7, 133, 33), // "on_doubleSpinBoxArgR_valueCha..."
QT_MOC_LITERAL(8, 167, 33), // "on_doubleSpinBoxArgB_valueCha..."
QT_MOC_LITERAL(9, 201, 34), // "emitSignalPowerTransformation..."
QT_MOC_LITERAL(10, 236, 19), // "powerTransformation"
QT_MOC_LITERAL(11, 256, 7), // "QImage*"
QT_MOC_LITERAL(12, 264, 11) // "originImage"

    },
    "DialogPowerTransformation\0"
    "signalPowerTransformationStart\0\0"
    "signalPowerTransformationEnd\0QImage&\0"
    "on_doubleSpinBoxArgC_valueChanged\0arg\0"
    "on_doubleSpinBoxArgR_valueChanged\0"
    "on_doubleSpinBoxArgB_valueChanged\0"
    "emitSignalPowerTransformationStart\0"
    "powerTransformation\0QImage*\0originImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogPowerTransformation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   53,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       8,    1,   59,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void DialogPowerTransformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogPowerTransformation *_t = static_cast<DialogPowerTransformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalPowerTransformationStart(); break;
        case 1: _t->signalPowerTransformationEnd((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->on_doubleSpinBoxArgC_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_doubleSpinBoxArgR_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_doubleSpinBoxArgB_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->emitSignalPowerTransformationStart(); break;
        case 6: _t->powerTransformation((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DialogPowerTransformation::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogPowerTransformation::signalPowerTransformationStart)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DialogPowerTransformation::*_t)(QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialogPowerTransformation::signalPowerTransformationEnd)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DialogPowerTransformation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogPowerTransformation.data,
      qt_meta_data_DialogPowerTransformation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DialogPowerTransformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogPowerTransformation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DialogPowerTransformation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DialogPowerTransformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DialogPowerTransformation::signalPowerTransformationStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DialogPowerTransformation::signalPowerTransformationEnd(QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
