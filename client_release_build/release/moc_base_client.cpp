/****************************************************************************
** Meta object code from reading C++ file 'base_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Client/BaseClient/base_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataTransfer__BaseClient_t {
    QByteArrayData data[8];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataTransfer__BaseClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataTransfer__BaseClient_t qt_meta_stringdata_DataTransfer__BaseClient = {
    {
QT_MOC_LITERAL(0, 0, 24), // "DataTransfer::BaseClient"
QT_MOC_LITERAL(1, 25, 12), // "socket_error"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(4, 68, 5), // "state"
QT_MOC_LITERAL(5, 74, 15), // "ready_data_read"
QT_MOC_LITERAL(6, 90, 16), // "connected_socket"
QT_MOC_LITERAL(7, 107, 19) // "disconnected_socket"

    },
    "DataTransfer::BaseClient\0socket_error\0"
    "\0QAbstractSocket::SocketError\0state\0"
    "ready_data_read\0connected_socket\0"
    "disconnected_socket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataTransfer__BaseClient[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,
       6,    0,   38,    2, 0x06 /* Public */,
       7,    0,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DataTransfer::BaseClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->socket_error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->ready_data_read(); break;
        case 2: _t->connected_socket(); break;
        case 3: _t->disconnected_socket(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseClient::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseClient::socket_error)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseClient::ready_data_read)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseClient::connected_socket)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BaseClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseClient::disconnected_socket)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataTransfer::BaseClient::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataTransfer__BaseClient.data,
    qt_meta_data_DataTransfer__BaseClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataTransfer::BaseClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataTransfer::BaseClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataTransfer__BaseClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataTransfer::BaseClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DataTransfer::BaseClient::socket_error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataTransfer::BaseClient::ready_data_read()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DataTransfer::BaseClient::connected_socket()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DataTransfer::BaseClient::disconnected_socket()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
