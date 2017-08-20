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
    QByteArrayData data[11];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qfPushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qfPushButton_t qt_meta_stringdata_qfPushButton = {
    {
QT_MOC_LITERAL(0, 0, 12), // "qfPushButton"
QT_MOC_LITERAL(1, 13, 22), // "deleteAction_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "btnIdx"
QT_MOC_LITERAL(4, 44, 21), // "show_rightClickedMenu"
QT_MOC_LITERAL(5, 66, 5), // "point"
QT_MOC_LITERAL(6, 72, 15), // "dialogBtnRename"
QT_MOC_LITERAL(7, 88, 25), // "on_btnRename_okBtn_pushed"
QT_MOC_LITERAL(8, 114, 30), // "on_btnEditCmd_action_triggered"
QT_MOC_LITERAL(9, 145, 26), // "on_btnEditCmd_okBtn_pushed"
QT_MOC_LITERAL(10, 172, 28) // "on_btnDeleteAction_triggered"

    },
    "qfPushButton\0deleteAction_triggered\0"
    "\0btnIdx\0show_rightClickedMenu\0point\0"
    "dialogBtnRename\0on_btnRename_okBtn_pushed\0"
    "on_btnEditCmd_action_triggered\0"
    "on_btnEditCmd_okBtn_pushed\0"
    "on_btnDeleteAction_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qfPushButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x08 /* Private */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void,
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
        case 0: _t->deleteAction_triggered((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->show_rightClickedMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->dialogBtnRename(); break;
        case 3: _t->on_btnRename_okBtn_pushed(); break;
        case 4: _t->on_btnEditCmd_action_triggered(); break;
        case 5: _t->on_btnEditCmd_okBtn_pushed(); break;
        case 6: _t->on_btnDeleteAction_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (qfPushButton::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&qfPushButton::deleteAction_triggered)) {
                *result = 0;
                return;
            }
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
void qfPushButton::deleteAction_triggered(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
