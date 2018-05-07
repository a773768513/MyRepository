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
    QByteArrayData data[18];
    char stringdata0[544];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CQThreadTextBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CQThreadTextBrowser_t qt_meta_stringdata_CQThreadTextBrowser = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CQThreadTextBrowser"
QT_MOC_LITERAL(1, 20, 17), // "EmitDataOutThread"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "char*"
QT_MOC_LITERAL(4, 45, 8), // "EmitData"
QT_MOC_LITERAL(5, 54, 34), // "On_this_CustomContextMenuRequ..."
QT_MOC_LITERAL(6, 89, 47), // "On_pTextBrowserMenuActionCont..."
QT_MOC_LITERAL(7, 137, 42), // "On_pHighlighterTextBrowserSel..."
QT_MOC_LITERAL(8, 180, 41), // "On_pCancelHighlightrTextBrows..."
QT_MOC_LITERAL(9, 222, 39), // "On_pTextBrowserMenuActionCopy..."
QT_MOC_LITERAL(10, 262, 44), // "On_pThreadTextBrowserStopWrit..."
QT_MOC_LITERAL(11, 307, 49), // "On_pThreadTextBrowserDeleteHi..."
QT_MOC_LITERAL(12, 357, 40), // "On_currentIndexChanged_pQComb..."
QT_MOC_LITERAL(13, 398, 5), // "index"
QT_MOC_LITERAL(14, 404, 48), // "On_pPushButtonClearHighlighti..."
QT_MOC_LITERAL(15, 453, 47), // "On_pPushButtonClearHighlighti..."
QT_MOC_LITERAL(16, 501, 21), // "AppendDataTextBrowser"
QT_MOC_LITERAL(17, 523, 20) // "pAppendDataCorespond"

    },
    "CQThreadTextBrowser\0EmitDataOutThread\0"
    "\0char*\0EmitData\0On_this_CustomContextMenuRequesred\0"
    "On_pTextBrowserMenuActionContinueData_Triggered\0"
    "On_pHighlighterTextBrowserSelect_Triggered\0"
    "On_pCancelHighlightrTextBrowser_Triggered\0"
    "On_pTextBrowserMenuActionCopy_Triggered\0"
    "On_pThreadTextBrowserStopWriteData_Triggered\0"
    "On_pThreadTextBrowserDeleteHighlihgting_Triggered\0"
    "On_currentIndexChanged_pQComboBoxShowStr\0"
    "index\0On_pPushButtonClearHighlightingComfirm_Triggered\0"
    "On_pPushButtonClearHighlightingCancel_Triggered\0"
    "AppendDataTextBrowser\0pAppendDataCorespond"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CQThreadTextBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   77,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    1,   86,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    0,   90,    2, 0x08 /* Private */,
      16,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   17,

       0        // eod
};

void CQThreadTextBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CQThreadTextBrowser *_t = static_cast<CQThreadTextBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EmitDataOutThread((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 1: _t->On_this_CustomContextMenuRequesred((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: _t->On_pTextBrowserMenuActionContinueData_Triggered(); break;
        case 3: _t->On_pHighlighterTextBrowserSelect_Triggered(); break;
        case 4: _t->On_pCancelHighlightrTextBrowser_Triggered(); break;
        case 5: _t->On_pTextBrowserMenuActionCopy_Triggered(); break;
        case 6: _t->On_pThreadTextBrowserStopWriteData_Triggered(); break;
        case 7: _t->On_pThreadTextBrowserDeleteHighlihgting_Triggered(); break;
        case 8: _t->On_currentIndexChanged_pQComboBoxShowStr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->On_pPushButtonClearHighlightingComfirm_Triggered(); break;
        case 10: _t->On_pPushButtonClearHighlightingCancel_Triggered(); break;
        case 11: _t->AppendDataTextBrowser((*reinterpret_cast< char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CQThreadTextBrowser::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CQThreadTextBrowser::EmitDataOutThread)) {
                *result = 0;
                return;
            }
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CQThreadTextBrowser::EmitDataOutThread(char * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
