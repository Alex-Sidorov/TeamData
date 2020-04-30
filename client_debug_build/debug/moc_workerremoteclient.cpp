/****************************************************************************
** Meta object code from reading C++ file 'workerremoteclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Client/workerremoteclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'workerremoteclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WorkerRemoteClient_t {
    QByteArrayData data[11];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerRemoteClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerRemoteClient_t qt_meta_stringdata_WorkerRemoteClient = {
    {
QT_MOC_LITERAL(0, 0, 18), // "WorkerRemoteClient"
QT_MOC_LITERAL(1, 19, 15), // "error_name_file"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15), // "error_open_file"
QT_MOC_LITERAL(4, 52, 21), // "error_connect_to_host"
QT_MOC_LITERAL(5, 74, 22), // "error_didnt_found_file"
QT_MOC_LITERAL(6, 97, 15), // "connect_to_host"
QT_MOC_LITERAL(7, 113, 15), // "downloaded_file"
QT_MOC_LITERAL(8, 129, 15), // "slot_ready_read"
QT_MOC_LITERAL(9, 145, 11), // "QTcpSocket*"
QT_MOC_LITERAL(10, 157, 6) // "socket"

    },
    "WorkerRemoteClient\0error_name_file\0\0"
    "error_open_file\0error_connect_to_host\0"
    "error_didnt_found_file\0connect_to_host\0"
    "downloaded_file\0slot_ready_read\0"
    "QTcpSocket*\0socket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerRemoteClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,
       7,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void WorkerRemoteClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WorkerRemoteClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error_name_file(); break;
        case 1: _t->error_open_file(); break;
        case 2: _t->error_connect_to_host(); break;
        case 3: _t->error_didnt_found_file(); break;
        case 4: _t->connect_to_host(); break;
        case 5: _t->downloaded_file(); break;
        case 6: _t->slot_ready_read((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::error_name_file)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::error_open_file)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::error_connect_to_host)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::error_didnt_found_file)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::connect_to_host)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WorkerRemoteClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerRemoteClient::downloaded_file)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WorkerRemoteClient::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WorkerRemoteClient.data,
    qt_meta_data_WorkerRemoteClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WorkerRemoteClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerRemoteClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerRemoteClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WorkerRemoteClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WorkerRemoteClient::error_name_file()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WorkerRemoteClient::error_open_file()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WorkerRemoteClient::error_connect_to_host()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WorkerRemoteClient::error_didnt_found_file()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WorkerRemoteClient::connect_to_host()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WorkerRemoteClient::downloaded_file()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
