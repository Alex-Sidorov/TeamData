/****************************************************************************
** Meta object code from reading C++ file 'workermetadata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Client/FileSystemWatcher/workermetadata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'workermetadata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WorkerMetaData_t {
    QByteArrayData data[11];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerMetaData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerMetaData_t qt_meta_stringdata_WorkerMetaData = {
    {
QT_MOC_LITERAL(0, 0, 14), // "WorkerMetaData"
QT_MOC_LITERAL(1, 15, 11), // "upload_tree"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "MetaDataDir"
QT_MOC_LITERAL(4, 40, 4), // "data"
QT_MOC_LITERAL(5, 45, 9), // "new_files"
QT_MOC_LITERAL(6, 55, 12), // "FileMetaData"
QT_MOC_LITERAL(7, 68, 13), // "removed_files"
QT_MOC_LITERAL(8, 82, 13), // "files_changed"
QT_MOC_LITERAL(9, 96, 4), // "path"
QT_MOC_LITERAL(10, 101, 11) // "dir_changed"

    },
    "WorkerMetaData\0upload_tree\0\0MetaDataDir\0"
    "data\0new_files\0FileMetaData\0removed_files\0"
    "files_changed\0path\0dir_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerMetaData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 6,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void WorkerMetaData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WorkerMetaData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upload_tree((*reinterpret_cast< MetaDataDir(*)>(_a[1]))); break;
        case 1: _t->new_files((*reinterpret_cast< FileMetaData(*)>(_a[1]))); break;
        case 2: _t->removed_files((*reinterpret_cast< FileMetaData(*)>(_a[1]))); break;
        case 3: _t->files_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->dir_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WorkerMetaData::*)(MetaDataDir );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerMetaData::upload_tree)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WorkerMetaData::*)(FileMetaData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerMetaData::new_files)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WorkerMetaData::*)(FileMetaData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerMetaData::removed_files)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WorkerMetaData::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WorkerMetaData.data,
    qt_meta_data_WorkerMetaData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WorkerMetaData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerMetaData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerMetaData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WorkerMetaData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WorkerMetaData::upload_tree(MetaDataDir _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WorkerMetaData::new_files(FileMetaData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WorkerMetaData::removed_files(FileMetaData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
