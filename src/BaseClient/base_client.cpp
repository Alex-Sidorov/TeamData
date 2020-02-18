#include "base_client.h"

namespace dt = DataTransfer;

dt::BaseClient::BaseClient(const QString &addr,quint16 port) :
    _addr(addr),
    _port(port),
    _mutex(nullptr),
    _wait_for_bytes_written(30000),
    _wait_for_connect(30000)
{
    connect(&_socket, &QTcpSocket::readyRead, this, &BaseClient::ready_data_read);
    connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &BaseClient::socket_error);
    connect(&_socket, &QTcpSocket::disconnected, this, &BaseClient::disconnected_socket);
}

bool dt::BaseClient::connect_to_host()
{
    QMutexLocker lock(_mutex);
    if(is_connected())
    {
        disconnect_to_host();
    }
    _socket.connectToHost(_addr,_port);
    return _socket.waitForConnected(_wait_for_connect);
}

void dt::BaseClient::disconnect_to_host()
{
    QMutexLocker lock(_mutex);
    if(is_connected())
    {
        _socket.disconnectFromHost();
    }
}

bool dt::BaseClient::write_data(QByteArray &data)
{
    QMutexLocker lock(_mutex);
    if(is_connected() && !data.isEmpty())
    {
        _socket.write(QByteArray::number(data.size()));
        _socket.write(data);
        return _socket.waitForBytesWritten(_wait_for_bytes_written);
    }
    return false;
}


bool dt::BaseClient::read_data(QByteArray &data)
{
    QMutexLocker lock(_mutex);
    if(is_connected() && _socket.bytesAvailable())
    {
        data = _socket.readAll();
        return true;
    }
    return false;
}


void dt::BaseClient::set_mutex(QMutex *mutex)
{
    if(!_mutex)
    {
        _mutex = mutex;
    }
}

void dt::BaseClient::set_wait_for_bytes_written(int value)
{
    _wait_for_bytes_written = value;
}

void dt::BaseClient::set_wait_for_connect(int value)
{
    _wait_for_connect = value;
}

bool dt::BaseClient::is_connected() const
{
    return _socket.state() == QAbstractSocket::SocketState::ConnectedState;
}

dt::BaseClient::~BaseClient()
{

}

