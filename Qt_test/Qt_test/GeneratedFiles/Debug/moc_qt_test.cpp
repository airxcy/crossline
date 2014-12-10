/****************************************************************************
** Meta object code from reading C++ file 'qt_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qt_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Qt_test_t {
    QByteArrayData data[17];
    char stringdata[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Qt_test_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Qt_test_t qt_meta_stringdata_Qt_test = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 9),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 7),
QT_MOC_LITERAL(4, 27, 11),
QT_MOC_LITERAL(5, 39, 3),
QT_MOC_LITERAL(6, 43, 13),
QT_MOC_LITERAL(7, 57, 11),
QT_MOC_LITERAL(8, 69, 11),
QT_MOC_LITERAL(9, 81, 6),
QT_MOC_LITERAL(10, 88, 13),
QT_MOC_LITERAL(11, 102, 13),
QT_MOC_LITERAL(12, 116, 10),
QT_MOC_LITERAL(13, 127, 14),
QT_MOC_LITERAL(14, 142, 14),
QT_MOC_LITERAL(15, 157, 1),
QT_MOC_LITERAL(16, 159, 1)
    },
    "Qt_test\0startusdc\0\0smthing\0const char*\0"
    "msg\0updateFrameUI\0debugMsgBox\0ucsdclicked\0"
    "initUI\0setLinePoints\0folderClicked\0"
    "aviClicked\0restartClicked\0updatePixLabel\0"
    "x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Qt_test[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   73,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x0a /* Public */,
       9,    0,   78,    2, 0x0a /* Public */,
      10,    2,   79,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    2,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,   16,

       0        // eod
};

void Qt_test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Qt_test *_t = static_cast<Qt_test *>(_o);
        switch (_id) {
        case 0: _t->startusdc(); break;
        case 1: _t->smthing((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->updateFrameUI(); break;
        case 3: _t->debugMsgBox((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 4: _t->ucsdclicked(); break;
        case 5: _t->initUI(); break;
        case 6: _t->setLinePoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->folderClicked(); break;
        case 8: _t->aviClicked(); break;
        case 9: _t->restartClicked(); break;
        case 10: _t->updatePixLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Qt_test::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Qt_test::startusdc)) {
                *result = 0;
            }
        }
        {
            typedef void (Qt_test::*_t)(const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Qt_test::smthing)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Qt_test::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Qt_test.data,
      qt_meta_data_Qt_test,  qt_static_metacall, 0, 0}
};


const QMetaObject *Qt_test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Qt_test::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Qt_test.stringdata))
        return static_cast<void*>(const_cast< Qt_test*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Qt_test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Qt_test::startusdc()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Qt_test::smthing(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
