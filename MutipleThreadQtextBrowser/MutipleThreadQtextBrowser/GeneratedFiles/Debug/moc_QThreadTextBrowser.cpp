/****************************************************************************
** Meta object code from reading C++ file 'QThreadTextBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QThreadTextBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QThreadTextBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CQThreadTextBrowser_t {
    QByteArrayData data[8];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQThreadTextBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQThreadTextBrowser_t qt_meta_stringdata_CQThreadTextBrowser = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CQThreadTextBrowser"
QT_MOC_LITERAL(1, 20, 34), // "On_this_CustomContextMenuRequ..."
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 47), // "On_pTextBrowserMenuActionCont..."
QT_MOC_LITERAL(4, 104, 42), // "On_pHighlighterTextBrowserSel..."
QT_MOC_LITERAL(5, 147, 41), // "On_pCancelHighlightrTextBrows..."
QT_MOC_LITERAL(6, 189, 39), // "On_pTextBrowserMenuActionCopy..."
QT_MOC_LITERAL(7, 229, 44) // "On_pThreadTextBrowserStopWrit..."

    },
    "CQThreadTextBrowser\0"
    "On_this_CustomContextMenuRequesred\0\0"
    "On_pTextBrowserMenuActionContinueData_Triggered\0"
    "On_pHighlighterTextBrowserSelect_Triggered\0"
    "On_pCancelHighlightrTextBrowser_Triggered\0"
    "On_pTextBrowserMenuActionCopy_Triggered\0"
    "On_pThreadTextBrowserStopWriteData_Triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQThreadTextBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       3,    0,   47,    2, 0x08 /* Private */,
       4,    0,   48,    2, 0x08 /* Private */,
       5,    0,   49,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CQThreadTextBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQThreadTextBrowser *_t = static_cast<CQThreadTextBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->On_this_CustomContextMenuRequesred((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->On_pTextBrowserMenuActionContinueData_Triggered(); break;
        case 2: _t->On_pHighlighterTextBrowserSelect_Triggered(); break;
        case 3: _t->On_pCancelHighlightrTextBrowser_Triggered(); break;
        case 4: _t->On_pTextBrowserMenuActionCopy_Triggered(); break;
        case 5: _t->On_pThreadTextBrowserStopWriteData_Triggered(); break;
        default: ;
        }
    }
}

const QMetaObject CQThreadTextBrowser::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_CQThreadTextBrowser.data,
      qt_meta_data_CQThreadTextBrowser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CQThreadTextBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CQThreadTextBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CQThreadTextBrowser.stringdata0))
        return static_cast<void*>(const_cast< CQThreadTextBrowser*>(this));
    return QTextBrowser::qt_metacast(_clname);
}

int CQThreadTextBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
