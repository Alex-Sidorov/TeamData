/****************************************************************************
** Meta object code from reading C++ file 'base_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Server/BaseServer/base_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataTransfer__BaseServer_t {
    QByteArrayData data[10];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataTransfer__BaseServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataTransfer__BaseServer_t qt_meta_stringdata_DataTransfer__BaseServer = {
    {
QT_MOC_LITERAL(0, 0, 24), // "DataTransfer::BaseServer"
QT_MOC_LITERAL(1, 25, 14), // "new_connection"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 12), // "socket_error"
QT_MOC_LITERAL(4, 54, 11), // "QTcpSocket*"
QT_MOC_LITERAL(5, 66, 6), // "socket"
QT_MOC_LITERAL(6, 73, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(7, 102, 5), // "state"
QT_MOC_LITERAL(8, 108, 15), // "ready_data_read"
QT_MOC_LITERAL(9, 124, 19) // "disconnected_socket"

    },
    "DataTransfer::BaseServer\0new_connection\0"
    "\0socket_error\0QTcpSocket*\0socket\0"
    "QAbstractSocket::SocketError\0state\0"
    "ready_data_read\0disconnected_socket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataTransfer__BaseServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,
       9,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void DataTransfer::BaseServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_connection(); break;
        case 1: _t->socket_error((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[2]))); break;
        case 2: _t->ready_data_read((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 3: _t->disconnected_socket((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        case 3:
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
            using _t = void (BaseServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseServer::new_connection)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseServer::*)(QTcpSocket * , QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseServer::socket_error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseServer::*)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseServer::ready_data_read)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BaseServer::*)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseServer::disconnected_socket)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataTransfer::BaseServer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataTransfer__BaseServer.data,
    qt_meta_data_DataTransfer__BaseServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataTransfer::BaseServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataTransfer::BaseServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataTransfer__BaseServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataTransfer::BaseServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DataTransfer::BaseServer::new_connection()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DataTransfer::BaseServer::socket_error(QTcpSocket * _t1, QAbstractSocket::SocketError _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataTransfer::BaseServer::ready_data_read(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataTransfer::BaseServer::disconnected_socket(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
