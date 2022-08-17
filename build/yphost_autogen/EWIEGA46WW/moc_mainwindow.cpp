/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "m_timer"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13), // "hk_cam_f_show"
QT_MOC_LITERAL(4, 34, 16), // "hk_cam_f_rb_open"
QT_MOC_LITERAL(5, 51, 13), // "hk_cam_u_show"
QT_MOC_LITERAL(6, 65, 16), // "hk_cam_u_rb_open"
QT_MOC_LITERAL(7, 82, 11), // "hk_cam_save"
QT_MOC_LITERAL(8, 94, 12), // "state_change"
QT_MOC_LITERAL(9, 107, 12), // "car_img_show"
QT_MOC_LITERAL(10, 120, 13), // "car_img1_show"
QT_MOC_LITERAL(11, 134, 19), // "car_status_feedback"
QT_MOC_LITERAL(12, 154, 6), // "float*"
QT_MOC_LITERAL(13, 161, 8), // "uart_val"
QT_MOC_LITERAL(14, 170, 11), // "car_command"
QT_MOC_LITERAL(15, 182, 12), // "car_command2"
QT_MOC_LITERAL(16, 195, 3), // "val"
QT_MOC_LITERAL(17, 199, 12), // "car_command3"
QT_MOC_LITERAL(18, 212, 8) // "car_init"

    },
    "MainWindow\0m_timer\0\0hk_cam_f_show\0"
    "hk_cam_f_rb_open\0hk_cam_u_show\0"
    "hk_cam_u_rb_open\0hk_cam_save\0state_change\0"
    "car_img_show\0car_img1_show\0"
    "car_status_feedback\0float*\0uart_val\0"
    "car_command\0car_command2\0val\0car_command3\0"
    "car_init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x09 /* Protected */,
       3,    1,   85,    2, 0x09 /* Protected */,
       4,    0,   88,    2, 0x09 /* Protected */,
       5,    1,   89,    2, 0x09 /* Protected */,
       6,    0,   92,    2, 0x09 /* Protected */,
       7,    0,   93,    2, 0x09 /* Protected */,
       8,    0,   94,    2, 0x09 /* Protected */,
       9,    1,   95,    2, 0x09 /* Protected */,
      10,    1,   98,    2, 0x09 /* Protected */,
      11,    1,  101,    2, 0x09 /* Protected */,
      14,    0,  104,    2, 0x09 /* Protected */,
      15,    1,  105,    2, 0x09 /* Protected */,
      17,    0,  108,    2, 0x09 /* Protected */,
      18,    0,  109,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->m_timer(); break;
        case 1: _t->hk_cam_f_show((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->hk_cam_f_rb_open(); break;
        case 3: _t->hk_cam_u_show((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 4: _t->hk_cam_u_rb_open(); break;
        case 5: _t->hk_cam_save(); break;
        case 6: _t->state_change(); break;
        case 7: _t->car_img_show((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 8: _t->car_img1_show((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 9: _t->car_status_feedback((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 10: _t->car_command(); break;
        case 11: _t->car_command2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->car_command3(); break;
        case 13: _t->car_init(); break;
        default: ;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
