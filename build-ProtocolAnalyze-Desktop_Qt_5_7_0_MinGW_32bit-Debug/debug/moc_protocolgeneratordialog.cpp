/****************************************************************************
** Meta object code from reading C++ file 'protocolgeneratordialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ProtocolAnalyze/protocolgeneratordialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocolgeneratordialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProtocolGeneratorDialog_t {
    QByteArrayData data[13];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProtocolGeneratorDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProtocolGeneratorDialog_t qt_meta_stringdata_ProtocolGeneratorDialog = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ProtocolGeneratorDialog"
QT_MOC_LITERAL(1, 24, 8), // "addParam"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 27), // "on_treeWidget_doubleClicked"
QT_MOC_LITERAL(4, 62, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 79, 4), // "item"
QT_MOC_LITERAL(6, 84, 5), // "colum"
QT_MOC_LITERAL(7, 90, 26), // "on_pushBtn_addRoot_clicked"
QT_MOC_LITERAL(8, 117, 26), // "on_pushBtn_addNode_clicked"
QT_MOC_LITERAL(9, 144, 29), // "on_pushBtn_deleteItem_clicked"
QT_MOC_LITERAL(10, 174, 31), // "on_pushBtn_saveSettings_clicked"
QT_MOC_LITERAL(11, 206, 31), // "on_pushBtn_loadSettings_clicked"
QT_MOC_LITERAL(12, 238, 27) // "on_pushBtn_generate_clicked"

    },
    "ProtocolGeneratorDialog\0addParam\0\0"
    "on_treeWidget_doubleClicked\0"
    "QTreeWidgetItem*\0item\0colum\0"
    "on_pushBtn_addRoot_clicked\0"
    "on_pushBtn_addNode_clicked\0"
    "on_pushBtn_deleteItem_clicked\0"
    "on_pushBtn_saveSettings_clicked\0"
    "on_pushBtn_loadSettings_clicked\0"
    "on_pushBtn_generate_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProtocolGeneratorDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    2,   55,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ProtocolGeneratorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProtocolGeneratorDialog *_t = static_cast<ProtocolGeneratorDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addParam(); break;
        case 1: _t->on_treeWidget_doubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_pushBtn_addRoot_clicked(); break;
        case 3: _t->on_pushBtn_addNode_clicked(); break;
        case 4: _t->on_pushBtn_deleteItem_clicked(); break;
        case 5: _t->on_pushBtn_saveSettings_clicked(); break;
        case 6: _t->on_pushBtn_loadSettings_clicked(); break;
        case 7: _t->on_pushBtn_generate_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ProtocolGeneratorDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProtocolGeneratorDialog.data,
      qt_meta_data_ProtocolGeneratorDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProtocolGeneratorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProtocolGeneratorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProtocolGeneratorDialog.stringdata0))
        return static_cast<void*>(const_cast< ProtocolGeneratorDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProtocolGeneratorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
