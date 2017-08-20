/****************************************************************************
** Meta object code from reading C++ file 'qfpushbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProtocolAnalyze/qfpushbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qfpushbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_qfPushButton_t {
    QByteArrayData data[8];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qfPushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qfPushButton_t qt_meta_stringdata_qfPushButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "qfPushButton"
QT_MOC_LITERAL(1, 13, 21), // "show_rightClickedMenu"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "point"
QT_MOC_LITERAL(4, 42, 15), // "dialogBtnRename"
QT_MOC_LITERAL(5, 58, 25), // "on_btnRename_okBtn_pushed"
QT_MOC_LITERAL(6, 84, 30), // "on_btnEditCmd_action_triggered"
QT_MOC_LITERAL(7, 115, 26) // "on_btnEditCmd_okBtn_pushed"

    },
    "qfPushButton\0show_rightClickedMenu\0\0"
    "point\0dialogBtnRename\0on_btnRename_okBtn_pushed\0"
    "on_btnEditCmd_action_triggered\0"
    "on_btnEditCmd_okBtn_pushed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qfPushButton[] = {

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
       1,    1,   39,    2, 0x08 /* Private */,
       4,    0,   42,    2, 0x08 /* Private */,
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void qfPushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        qfPushButton *_t = static_cast<qfPushButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show_rightClickedMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->dialogBtnRename(); break;
        case 2: _t->on_btnRename_okBtn_pushed(); break;
        case 3: _t->on_btnEditCmd_action_triggered(); break;
        case 4: _t->on_btnEditCmd_okBtn_pushed(); break;
        default: ;
        }
    }
}

const QMetaObject qfPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_qfPushButton.data,
      qt_meta_data_qfPushButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *qfPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qfPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_qfPushButton.stringdata0))
        return static_cast<void*>(const_cast< qfPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int qfPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
