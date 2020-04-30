/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Client/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 29), // "on_select_path_button_clicked"
QT_MOC_LITERAL(4, 64, 17), // "slot_removed_dirs"
QT_MOC_LITERAL(5, 82, 4), // "dirs"
QT_MOC_LITERAL(6, 87, 14), // "slot_load_tree"
QT_MOC_LITERAL(7, 102, 27), // "WorkerMetaData::MetaDataDir"
QT_MOC_LITERAL(8, 130, 4), // "data"
QT_MOC_LITERAL(9, 135, 4), // "name"
QT_MOC_LITERAL(10, 140, 22), // "on_users_doubleClicked"
QT_MOC_LITERAL(11, 163, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 175, 5), // "index"
QT_MOC_LITERAL(13, 181, 28), // "on_name_line_editingFinished"
QT_MOC_LITERAL(14, 210, 28), // "on_self_addr_editingFinished"
QT_MOC_LITERAL(15, 239, 28), // "on_serv_addr_editingFinished"
QT_MOC_LITERAL(16, 268, 25), // "on_serv_port_valueChanged"
QT_MOC_LITERAL(17, 294, 4), // "arg1"
QT_MOC_LITERAL(18, 299, 25), // "on_self_port_valueChanged"
QT_MOC_LITERAL(19, 325, 28), // "on_path_line_editingFinished"
QT_MOC_LITERAL(20, 354, 20), // "on_work_serv_clicked"
QT_MOC_LITERAL(21, 375, 29), // "on_tree_dir_itemDoubleClicked"
QT_MOC_LITERAL(22, 405, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(23, 422, 4), // "item"
QT_MOC_LITERAL(24, 427, 6) // "column"

    },
    "MainWindow\0on_pushButton_clicked\0\0"
    "on_select_path_button_clicked\0"
    "slot_removed_dirs\0dirs\0slot_load_tree\0"
    "WorkerMetaData::MetaDataDir\0data\0name\0"
    "on_users_doubleClicked\0QModelIndex\0"
    "index\0on_name_line_editingFinished\0"
    "on_self_addr_editingFinished\0"
    "on_serv_addr_editingFinished\0"
    "on_serv_port_valueChanged\0arg1\0"
    "on_self_port_valueChanged\0"
    "on_path_line_editingFinished\0"
    "on_work_serv_clicked\0on_tree_dir_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    1,   81,    2, 0x08 /* Private */,
       6,    2,   84,    2, 0x08 /* Private */,
      10,    1,   89,    2, 0x08 /* Private */,
      13,    0,   92,    2, 0x08 /* Private */,
      14,    0,   93,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    1,   95,    2, 0x08 /* Private */,
      18,    1,   98,    2, 0x08 /* Private */,
      19,    0,  101,    2, 0x08 /* Private */,
      20,    0,  102,    2, 0x08 /* Private */,
      21,    2,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, QMetaType::Int,   23,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_select_path_button_clicked(); break;
        case 2: _t->slot_removed_dirs((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->slot_load_tree((*reinterpret_cast< WorkerMetaData::MetaDataDir(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->on_users_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_name_line_editingFinished(); break;
        case 6: _t->on_self_addr_editingFinished(); break;
        case 7: _t->on_serv_addr_editingFinished(); break;
        case 8: _t->on_serv_port_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_self_port_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_path_line_editingFinished(); break;
        case 11: _t->on_work_serv_clicked(); break;
        case 12: _t->on_tree_dir_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
