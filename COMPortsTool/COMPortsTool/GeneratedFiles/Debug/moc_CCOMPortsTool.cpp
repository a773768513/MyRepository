/****************************************************************************
** Meta object code from reading C++ file 'CCOMPortsTool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CCOMPortsTool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CCOMPortsTool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCOMPortsTool_t {
    QByteArrayData data[11];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCOMPortsTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCOMPortsTool_t qt_meta_stringdata_CCOMPortsTool = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CCOMPortsTool"
QT_MOC_LITERAL(1, 14, 33), // "On_pConnectDialogAction_Trigg..."
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 35), // "On_pQConnectOpenFileConfirm_C..."
QT_MOC_LITERAL(4, 85, 34), // "On_pQConnectOpenFileCancel_Cl..."
QT_MOC_LITERAL(5, 120, 30), // "On_tabCloseRequested_Triggered"
QT_MOC_LITERAL(6, 151, 12), // "CurrentIndex"
QT_MOC_LITERAL(7, 164, 40), // "On_pQOpenWriteFileDialogActio..."
QT_MOC_LITERAL(8, 205, 34), // "On_pQWriteDialogFileButton_cl..."
QT_MOC_LITERAL(9, 240, 37), // "On_pQWriteDialogConfirmButton..."
QT_MOC_LITERAL(10, 278, 36) // "On_pQWriteDialogCancelButton_..."

    },
    "CCOMPortsTool\0On_pConnectDialogAction_Triggered\0"
    "\0On_pQConnectOpenFileConfirm_Clicked\0"
    "On_pQConnectOpenFileCancel_Clicked\0"
    "On_tabCloseRequested_Triggered\0"
    "CurrentIndex\0On_pQOpenWriteFileDialogAction_Triggered\0"
    "On_pQWriteDialogFileButton_clicked\0"
    "On_pQWriteDialogConfirmButton_clicked\0"
    "On_pQWriteDialogCancelButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCOMPortsTool[] = {

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
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CCOMPortsTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CCOMPortsTool *_t = static_cast<CCOMPortsTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->On_pConnectDialogAction_Triggered(); break;
        case 1: _t->On_pQConnectOpenFileConfirm_Clicked(); break;
        case 2: _t->On_pQConnectOpenFileCancel_Clicked(); break;
        case 3: _t->On_tabCloseRequested_Triggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->On_pQOpenWriteFileDialogAction_Triggered(); break;
        case 5: _t->On_pQWriteDialogFileButton_clicked(); break;
        case 6: _t->On_pQWriteDialogConfirmButton_clicked(); break;
        case 7: _t->On_pQWriteDialogCancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject CCOMPortsTool::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CCOMPortsTool.data,
      qt_meta_data_CCOMPortsTool,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CCOMPortsTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCOMPortsTool::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CCOMPortsTool.stringdata0))
        return static_cast<void*>(const_cast< CCOMPortsTool*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CCOMPortsTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
