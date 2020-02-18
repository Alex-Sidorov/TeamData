#include "base_server.h"

namespace dt = DataTransfer;

dt::BaseServer::BaseServer(const QString &addr,quint16 port) :
    _addr(addr),
    _port(port),
    _mutex(nullptr),
    _wait_for_bytes_written(30000)
{
     connect(&_server,&QTcpServer::newConnection,this,&BaseServer::new_connection);
}

bool dt::BaseServer::run()
{
    QMutexLocker lock(_mutex);
    if(!_server.listen(QHostAddress(_addr),_port))
    {
        return false;
    }
    return true;
}

void dt::BaseServer::stop()
{
    QMutexLocker lock(_mutex);
    foreach(auto item,_sockets)
    {
        remove_connection(item);
    }
    _server.close();
}

void dt::BaseServer::remove_connection(int index)
{
    QMutexLocker lock(_mutex);
    if(index >= 0 && index < _sockets.count())
    {
        if(_mutex)
        {
            _sockets_mutexes.remove(_sockets[index]);
        }
        _sockets[index]->disconnectFromHost();
        _sockets[index]->deleteLater();
        _sockets.removeAt(index);
    }
}

void dt::BaseServer::remove_connection(QTcpSocket *socket)
{
    QMutexLocker lock(_mutex);
    if(_sockets.indexOf(socket) != -1)
    {
        if(_mutex)
        {
            _sockets_mutexes.remove(socket);
        }
        socket->disconnectFromHost();
        socket->deleteLater();
        _sockets.removeOne(socket);
    }
}

void dt::BaseServer::add_connection()
{
    QMutexLocker lock(_mutex);
    if(_server.hasPendingConnections())
    {
        QTcpSocket *client = _server.nextPendingConnection();

        connect(client, &QTcpSocket::readyRead, [&]()
        {
            emit ready_data_read(static_cast<QTcpSocket*>(QObject::sender()));
        });

        connect(client, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [&](QAbstractSocket::SocketError error)
        {
            emit socket_error(static_cast<QTcpSocket*>(QObject::sender()),error);
        });

        connect(client, &QTcpSocket::disconnected,[&]()
        {
            emit disconnected_socket(static_cast<QTcpSocket*>(QObject::sender()));
        });

        if(_mutex)
        {
            _sockets_mutexes.insert(client, QSharedPointer<QMutex>());
        }
        _sockets.push_back(client);
    }
}

bool dt::BaseServer::write_data(QTcpSocket *socket, QByteArray &data)
{
    bool is_thread_safe = _sockets_mutexes.find(socket) != _sockets_mutexes.end();
    QMutexLocker lock(is_thread_safe ? _sockets_mutexes[socket].get() : nullptr);

    if(is_valid_socket(socket)  && !data.isEmpty())
    {
        socket->write(QByteArray::number(data.size()));
        socket->write(data);
        return socket->waitForBytesWritten(_wait_for_bytes_written);
    }
    return false;
}

bool dt::BaseServer::read_data(QTcpSocket *socket, QByteArray &data)
{
    bool is_thread_safe = _sockets_mutexes.find(socket) != _sockets_mutexes.end();
    QMutexLocker lock(is_thread_safe ? _sockets_mutexes[socket].get() : nullptr);

    if(is_valid_socket(socket) && socket->bytesAvailable())
    {
        data = socket->readAll();
        return true;
    }
    return false;
}

bool dt::BaseServer::is_valid_socket(QTcpSocket *socket) const
{
    return _sockets.indexOf(socket) != -1
            && socket->state() == QAbstractSocket::ConnectedState;
}

void dt::BaseServer::set_mutex(QMutex *mutex)
{
    if(!_mutex)
    {
        _mutex = mutex;
    }
}

void dt::BaseServer::set_wait_for_bytes_written(int value)
{
    _wait_for_bytes_written = value;
}

dt::BaseServer::~BaseServer()
{

}
