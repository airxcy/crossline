/****************************************************************************
** Meta object code from reading C++ file 'StreamThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../StreamThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StreamThread_t {
    QByteArrayData data[14];
    char stringdata[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamThread_t qt_meta_stringdata_StreamThread = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5),
QT_MOC_LITERAL(4, 31, 11),
QT_MOC_LITERAL(5, 43, 3),
QT_MOC_LITERAL(6, 47, 6),
QT_MOC_LITERAL(7, 54, 11),
QT_MOC_LITERAL(8, 66, 6),
QT_MOC_LITERAL(9, 73, 4),
QT_MOC_LITERAL(10, 78, 1),
QT_MOC_LITERAL(11, 80, 1),
QT_MOC_LITERAL(12, 82, 1),
QT_MOC_LITERAL(13, 84, 4)
    },
    "StreamThread\0aFrameDone\0\0debug\0"
    "const char*\0msg\0initUI\0streamStart\0"
    "string\0fstr\0l\0h\0w\0init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    4,   54,    2, 0x0a /* Public */,
       7,    3,   63,    2, 0x2a /* Public | MethodCloned */,
       7,    2,   70,    2, 0x2a /* Public | MethodCloned */,
      13,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,   12,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Bool,

       0        // eod
};

void StreamThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StreamThread *_t = static_cast<StreamThread *>(_o);
        switch (_id) {
        case 0: _t->aFrameDone(); break;
        case 1: _t->debug((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->initUI(); break;
        case 3: _t->streamStart((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->streamStart((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->streamStart((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: { bool _r = _t->init();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::aFrameDone)) {
                *result = 0;
            }
        }
        {
            typedef void (StreamThread::*_t)(const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::debug)) {
                *result = 1;
            }
        }
        {
            typedef void (StreamThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StreamThread::initUI)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject StreamThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_StreamThread.data,
      qt_meta_data_StreamThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *StreamThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StreamThread.stringdata))
        return static_cast<void*>(const_cast< StreamThread*>(this));
    return QThread::qt_metacast(_clname);
}

int StreamThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void StreamThread::aFrameDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void StreamThread::debug(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StreamThread::initUI()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
