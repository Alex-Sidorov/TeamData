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
    QByteArrayData data[16];
    char stringdata0[174];
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
QT_MOC_LITERAL(8, 82, 8), // "new_dirs"
QT_MOC_LITERAL(9, 91, 12), // "removed_dirs"
QT_MOC_LITERAL(10, 104, 13), // "files_changed"
QT_MOC_LITERAL(11, 118, 4), // "path"
QT_MOC_LITERAL(12, 123, 11), // "dir_changed"
QT_MOC_LITERAL(13, 135, 16), // "remove_root_path"
QT_MOC_LITERAL(14, 152, 8), // "QString&"
QT_MOC_LITERAL(15, 161, 12) // "QStringList&"

    },
    "WorkerMetaData\0upload_tree\0\0MetaDataDir\0"
    "data\0new_files\0FileMetaData\0removed_files\0"
    "new_dirs\0removed_dirs\0files_changed\0"
    "path\0dir_changed\0remove_root_path\0"
    "QString&\0QStringList&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerMetaData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,
       9,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   69,    2, 0x0a /* Public */,
      12,    1,   72,    2, 0x0a /* Public */,
      13,    2,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void, QMetaType::QStringList,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 15,   11,    4,

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
        case 3: _t->new_dirs((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->removed_dirs((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: _t->files_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->dir_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->remove_root_path((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
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
        {
            using _t = void (WorkerMetaData::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerMetaData::new_dirs)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WorkerMetaData::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WorkerMetaData::removed_dirs)) {
                *result = 4;
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

// SIGNAL 3
void WorkerMetaData::new_dirs(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WorkerMetaData::removed_dirs(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
