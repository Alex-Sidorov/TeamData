#include "workerusers.h"

QString WorkerUsers::get_self_addr()const
{
    return _self_addr;
}

quint16 WorkerUsers::get_self_port()const
{
    return _self_port;
}

WorkerUsers::WorkerUsers():
    _self_port(0)
{}

WorkerUsers::WorkerUsers(const QString &addr, const quint16 port) :
    _self_addr(addr),
    _self_port(port)
{}

WorkerUsers::~WorkerUsers()
{}
