#ifndef WORKERUSERS_H
#define WORKERUSERS_H

#include <QString>

class WorkerUsers
{
public:
    WorkerUsers();
    WorkerUsers(const QString &addr, const quint16 port);
    virtual ~WorkerUsers();

    QString get_self_addr()const;
    quint16 get_self_port()const;
private:
    QString _self_addr;
    quint16 _self_port;
};

#endif // WORKERUSERS_H
