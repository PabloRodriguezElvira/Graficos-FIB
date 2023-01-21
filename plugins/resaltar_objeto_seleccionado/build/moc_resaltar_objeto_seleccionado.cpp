/****************************************************************************
** Meta object code from reading C++ file 'resaltar_objeto_seleccionado.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../resaltar_objeto_seleccionado.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resaltar_objeto_seleccionado.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Resaltar_objeto_seleccionado_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Resaltar_objeto_seleccionado_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Resaltar_objeto_seleccionado_t qt_meta_stringdata_Resaltar_objeto_seleccionado = {
    {
QT_MOC_LITERAL(0, 0, 28) // "Resaltar_objeto_seleccionado"

    },
    "Resaltar_objeto_seleccionado"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Resaltar_objeto_seleccionado[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Resaltar_objeto_seleccionado::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Resaltar_objeto_seleccionado::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Resaltar_objeto_seleccionado.data,
    qt_meta_data_Resaltar_objeto_seleccionado,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Resaltar_objeto_seleccionado::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Resaltar_objeto_seleccionado::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Resaltar_objeto_seleccionado.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Plugin"))
        return static_cast< Plugin*>(this);
    if (!strcmp(_clname, "edu.upc.fib.graug.Plugin/1.0"))
        return static_cast< Plugin*>(this);
    return QObject::qt_metacast(_clname);
}

int Resaltar_objeto_seleccionado::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x66,  'P',  'l',  'u',  'g',  'i',  'n', 
    // "className"
    0x03,  0x78,  0x1c,  'R',  'e',  's',  'a',  'l', 
    't',  'a',  'r',  '_',  'o',  'b',  'j',  'e', 
    't',  'o',  '_',  's',  'e',  'l',  'e',  'c', 
    'c',  'i',  'o',  'n',  'a',  'd',  'o', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(Resaltar_objeto_seleccionado, Resaltar_objeto_seleccionado)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
