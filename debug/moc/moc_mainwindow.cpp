/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[42];
    char stringdata0[1143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "signalSendImage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "QImage*"
QT_MOC_LITERAL(4, 36, 19), // "emitSignalSendImage"
QT_MOC_LITERAL(5, 56, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(6, 80, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(7, 104, 25), // "on_actionSaveAs_triggered"
QT_MOC_LITERAL(8, 130, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(9, 155, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(10, 179, 34), // "on_actionSetSamplingRate_trig..."
QT_MOC_LITERAL(11, 214, 35), // "on_actionSetQuantifyLevel_tri..."
QT_MOC_LITERAL(12, 250, 40), // "on_actionSetGrayscaleThreshol..."
QT_MOC_LITERAL(13, 291, 34), // "on_actionDisplayBitPlane_trig..."
QT_MOC_LITERAL(14, 326, 35), // "on_actionDisplayHistogram_tri..."
QT_MOC_LITERAL(15, 362, 39), // "on_actionLinearTransformation..."
QT_MOC_LITERAL(16, 402, 36), // "on_actionLogTransformation_tr..."
QT_MOC_LITERAL(17, 439, 38), // "on_actionPowerTransformation_..."
QT_MOC_LITERAL(18, 478, 40), // "on_actionHistogramEqualizatio..."
QT_MOC_LITERAL(19, 519, 26), // "on_actionScaling_triggered"
QT_MOC_LITERAL(20, 546, 27), // "on_actionRotation_triggered"
QT_MOC_LITERAL(21, 574, 30), // "on_actionTranslation_triggered"
QT_MOC_LITERAL(22, 605, 30), // "on_actionSpectrogram_triggered"
QT_MOC_LITERAL(23, 636, 35), // "on_actionAverageFiltering_tri..."
QT_MOC_LITERAL(24, 672, 34), // "on_actionMedianFiltering_trig..."
QT_MOC_LITERAL(25, 707, 23), // "on_actionKNNF_triggered"
QT_MOC_LITERAL(26, 731, 24), // "on_actionKNNMF_triggered"
QT_MOC_LITERAL(27, 756, 26), // "on_actionReborts_triggered"
QT_MOC_LITERAL(28, 783, 24), // "on_actionSobel_triggered"
QT_MOC_LITERAL(29, 808, 28), // "on_actionLaplacian_triggered"
QT_MOC_LITERAL(30, 837, 36), // "on_actionEnhancedLaplacian_tr..."
QT_MOC_LITERAL(31, 874, 30), // "on_actionConvolution_triggered"
QT_MOC_LITERAL(32, 905, 25), // "on_actionToGray_triggered"
QT_MOC_LITERAL(33, 931, 24), // "on_actionTo256_triggered"
QT_MOC_LITERAL(34, 956, 28), // "on_actionEdgeSobel_triggered"
QT_MOC_LITERAL(35, 985, 30), // "on_actionEdgePrewitt_triggered"
QT_MOC_LITERAL(36, 1016, 32), // "on_actionEdgeLaplacian_triggered"
QT_MOC_LITERAL(37, 1049, 30), // "on_actionEdgeTracing_triggered"
QT_MOC_LITERAL(38, 1080, 28), // "on_actionEdgeHough_triggered"
QT_MOC_LITERAL(39, 1109, 16), // "updateRightImage"
QT_MOC_LITERAL(40, 1126, 7), // "QImage&"
QT_MOC_LITERAL(41, 1134, 8) // "newImage"

    },
    "MainWindow\0signalSendImage\0\0QImage*\0"
    "emitSignalSendImage\0on_actionOpen_triggered\0"
    "on_actionSave_triggered\0"
    "on_actionSaveAs_triggered\0"
    "on_actionClose_triggered\0"
    "on_actionQuit_triggered\0"
    "on_actionSetSamplingRate_triggered\0"
    "on_actionSetQuantifyLevel_triggered\0"
    "on_actionSetGrayscaleThreshold_triggered\0"
    "on_actionDisplayBitPlane_triggered\0"
    "on_actionDisplayHistogram_triggered\0"
    "on_actionLinearTransformation_triggered\0"
    "on_actionLogTransformation_triggered\0"
    "on_actionPowerTransformation_triggered\0"
    "on_actionHistogramEqualization_triggered\0"
    "on_actionScaling_triggered\0"
    "on_actionRotation_triggered\0"
    "on_actionTranslation_triggered\0"
    "on_actionSpectrogram_triggered\0"
    "on_actionAverageFiltering_triggered\0"
    "on_actionMedianFiltering_triggered\0"
    "on_actionKNNF_triggered\0"
    "on_actionKNNMF_triggered\0"
    "on_actionReborts_triggered\0"
    "on_actionSobel_triggered\0"
    "on_actionLaplacian_triggered\0"
    "on_actionEnhancedLaplacian_triggered\0"
    "on_actionConvolution_triggered\0"
    "on_actionToGray_triggered\0"
    "on_actionTo256_triggered\0"
    "on_actionEdgeSobel_triggered\0"
    "on_actionEdgePrewitt_triggered\0"
    "on_actionEdgeLaplacian_triggered\0"
    "on_actionEdgeTracing_triggered\0"
    "on_actionEdgeHough_triggered\0"
    "updateRightImage\0QImage&\0newImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  199,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  202,    2, 0x08 /* Private */,
       5,    0,  203,    2, 0x08 /* Private */,
       6,    0,  204,    2, 0x08 /* Private */,
       7,    0,  205,    2, 0x08 /* Private */,
       8,    0,  206,    2, 0x08 /* Private */,
       9,    0,  207,    2, 0x08 /* Private */,
      10,    0,  208,    2, 0x08 /* Private */,
      11,    0,  209,    2, 0x08 /* Private */,
      12,    0,  210,    2, 0x08 /* Private */,
      13,    0,  211,    2, 0x08 /* Private */,
      14,    0,  212,    2, 0x08 /* Private */,
      15,    0,  213,    2, 0x08 /* Private */,
      16,    0,  214,    2, 0x08 /* Private */,
      17,    0,  215,    2, 0x08 /* Private */,
      18,    0,  216,    2, 0x08 /* Private */,
      19,    0,  217,    2, 0x08 /* Private */,
      20,    0,  218,    2, 0x08 /* Private */,
      21,    0,  219,    2, 0x08 /* Private */,
      22,    0,  220,    2, 0x08 /* Private */,
      23,    0,  221,    2, 0x08 /* Private */,
      24,    0,  222,    2, 0x08 /* Private */,
      25,    0,  223,    2, 0x08 /* Private */,
      26,    0,  224,    2, 0x08 /* Private */,
      27,    0,  225,    2, 0x08 /* Private */,
      28,    0,  226,    2, 0x08 /* Private */,
      29,    0,  227,    2, 0x08 /* Private */,
      30,    0,  228,    2, 0x08 /* Private */,
      31,    0,  229,    2, 0x08 /* Private */,
      32,    0,  230,    2, 0x08 /* Private */,
      33,    0,  231,    2, 0x08 /* Private */,
      34,    0,  232,    2, 0x08 /* Private */,
      35,    0,  233,    2, 0x08 /* Private */,
      36,    0,  234,    2, 0x08 /* Private */,
      37,    0,  235,    2, 0x08 /* Private */,
      38,    0,  236,    2, 0x08 /* Private */,
      39,    1,  237,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 40,   41,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 1: _t->emitSignalSendImage(); break;
        case 2: _t->on_actionOpen_triggered(); break;
        case 3: _t->on_actionSave_triggered(); break;
        case 4: _t->on_actionSaveAs_triggered(); break;
        case 5: _t->on_actionClose_triggered(); break;
        case 6: _t->on_actionQuit_triggered(); break;
        case 7: _t->on_actionSetSamplingRate_triggered(); break;
        case 8: _t->on_actionSetQuantifyLevel_triggered(); break;
        case 9: _t->on_actionSetGrayscaleThreshold_triggered(); break;
        case 10: _t->on_actionDisplayBitPlane_triggered(); break;
        case 11: _t->on_actionDisplayHistogram_triggered(); break;
        case 12: _t->on_actionLinearTransformation_triggered(); break;
        case 13: _t->on_actionLogTransformation_triggered(); break;
        case 14: _t->on_actionPowerTransformation_triggered(); break;
        case 15: _t->on_actionHistogramEqualization_triggered(); break;
        case 16: _t->on_actionScaling_triggered(); break;
        case 17: _t->on_actionRotation_triggered(); break;
        case 18: _t->on_actionTranslation_triggered(); break;
        case 19: _t->on_actionSpectrogram_triggered(); break;
        case 20: _t->on_actionAverageFiltering_triggered(); break;
        case 21: _t->on_actionMedianFiltering_triggered(); break;
        case 22: _t->on_actionKNNF_triggered(); break;
        case 23: _t->on_actionKNNMF_triggered(); break;
        case 24: _t->on_actionReborts_triggered(); break;
        case 25: _t->on_actionSobel_triggered(); break;
        case 26: _t->on_actionLaplacian_triggered(); break;
        case 27: _t->on_actionEnhancedLaplacian_triggered(); break;
        case 28: _t->on_actionConvolution_triggered(); break;
        case 29: _t->on_actionToGray_triggered(); break;
        case 30: _t->on_actionTo256_triggered(); break;
        case 31: _t->on_actionEdgeSobel_triggered(); break;
        case 32: _t->on_actionEdgePrewitt_triggered(); break;
        case 33: _t->on_actionEdgeLaplacian_triggered(); break;
        case 34: _t->on_actionEdgeTracing_triggered(); break;
        case 35: _t->on_actionEdgeHough_triggered(); break;
        case 36: _t->updateRightImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(QImage * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalSendImage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalSendImage(QImage * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
