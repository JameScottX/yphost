/****************************************************************************
** Meta object code from reading C++ file 'car.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../car.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'car.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CAR_t {
    QByteArrayData data[7];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAR_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAR_t qt_meta_stringdata_CAR = {
    {
QT_MOC_LITERAL(0, 0, 3), // "CAR"
QT_MOC_LITERAL(1, 4, 7), // "car_img"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 8), // "car_img1"
QT_MOC_LITERAL(4, 22, 8), // "car_uart"
QT_MOC_LITERAL(5, 31, 6), // "float*"
QT_MOC_LITERAL(6, 38, 8) // "uart_val"

    },
    "CAR\0car_img\0\0car_img1\0car_uart\0float*\0"
    "uart_val"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAR[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,
       4,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void CAR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CAR *_t = static_cast<CAR *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->car_img((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->car_img1((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->car_uart((*reinterpret_cast< float*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (CAR::*_t)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAR::car_img)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CAR::*_t)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAR::car_img1)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CAR::*_t)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CAR::car_uart)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CAR::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CAR.data,
      qt_meta_data_CAR,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CAR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAR::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CAR.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CAR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CAR::car_img(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CAR::car_img1(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CAR::car_uart(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
