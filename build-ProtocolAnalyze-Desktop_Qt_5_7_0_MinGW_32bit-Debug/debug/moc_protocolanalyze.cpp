/****************************************************************************
** Meta object code from reading C++ file 'protocolanalyze.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProtocolAnalyze/protocolanalyze.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocolanalyze.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProtocolAnalyze_t {
    QByteArrayData data[16];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProtocolAnalyze_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProtocolAnalyze_t qt_meta_stringdata_ProtocolAnalyze = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ProtocolAnalyze"
QT_MOC_LITERAL(1, 16, 14), // "openSerialPort"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "closeSerialPort"
QT_MOC_LITERAL(4, 48, 29), // "on_pB_refreshPortInfo_clicked"
QT_MOC_LITERAL(5, 78, 24), // "on_pB_autoGenBtn_clicked"
QT_MOC_LITERAL(6, 103, 24), // "on_pB_autoGenBtn_pressed"
QT_MOC_LITERAL(7, 128, 8), // "readData"
QT_MOC_LITERAL(8, 137, 9), // "writeData"
QT_MOC_LITERAL(9, 147, 4), // "data"
QT_MOC_LITERAL(10, 152, 34), // "on_pushBtn_loadBtnSettings_cl..."
QT_MOC_LITERAL(11, 187, 34), // "on_pushBtn_saveBtnSettings_cl..."
QT_MOC_LITERAL(12, 222, 24), // "on_pushBtn_clear_clicked"
QT_MOC_LITERAL(13, 247, 21), // "show_rightClickedMenu"
QT_MOC_LITERAL(14, 269, 24), // "show_rightClickedBtnMenu"
QT_MOC_LITERAL(15, 294, 9) // "btnRename"

    },
    "ProtocolAnalyze\0openSerialPort\0\0"
    "closeSerialPort\0on_pB_refreshPortInfo_clicked\0"
    "on_pB_autoGenBtn_clicked\0"
    "on_pB_autoGenBtn_pressed\0readData\0"
    "writeData\0data\0on_pushBtn_loadBtnSettings_clicked\0"
    "on_pushBtn_saveBtnSettings_clicked\0"
    "on_pushBtn_clear_clicked\0show_rightClickedMenu\0"
    "show_rightClickedBtnMenu\0btnRename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProtocolAnalyze[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      14,    1,   94,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void ProtocolAnalyze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProtocolAnalyze *_t = static_cast<ProtocolAnalyze *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openSerialPort(); break;
        case 1: _t->closeSerialPort(); break;
        case 2: _t->on_pB_refreshPortInfo_clicked(); break;
        case 3: _t->on_pB_autoGenBtn_clicked(); break;
        case 4: _t->on_pB_autoGenBtn_pressed(); break;
        case 5: _t->readData(); break;
        case 6: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->on_pushBtn_loadBtnSettings_clicked(); break;
        case 8: _t->on_pushBtn_saveBtnSettings_clicked(); break;
        case 9: _t->on_pushBtn_clear_clicked(); break;
        case 10: _t->show_rightClickedMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->show_rightClickedBtnMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->btnRename(); break;
        default: ;
        }
    }
}

const QMetaObject ProtocolAnalyze::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ProtocolAnalyze.data,
      qt_meta_data_ProtocolAnalyze,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProtocolAnalyze::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProtocolAnalyze::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProtocolAnalyze.stringdata0))
        return static_cast<void*>(const_cast< ProtocolAnalyze*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ProtocolAnalyze::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
