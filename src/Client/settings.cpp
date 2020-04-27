#include "settings.h"

QString Settings::get_self_addr()const
{
    return _self_addr;
}

quint16 Settings::get_self_port()const
{
    return _self_port;
}

Settings::Settings():
    _self_port(0)
{}

Settings::Settings(const QString &addr, const quint16 port) :
    _self_addr(addr),
    _self_port(port)
{}

Settings::~Settings()
{}
