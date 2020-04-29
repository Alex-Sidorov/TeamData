#include "base_client.h"
#include <QDataStream>

namespace dt = DataTransfer;

dt::BaseClient::BaseClient(const QString &addr,quint16 port) :
    _serv_addr(addr),
    _serv_port(port),
    _wait_for_bytes_written(0),
    _wait_for_connect(0)
{
    connect(&_socket, &QTcpSocket::readyRead, this, &BaseClient::ready_data_read);
    connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &BaseClient::socket_error);
    connect(&_socket, &QTcpSocket::disconnected, this, &BaseClient::disconnected_socket);
    connect(&_socket, &QTcpSocket::connected, this, &BaseClient::connected_socket);
}

void dt::BaseClient::connect_to_host()
{
    if(is_connected())
    {
        disconnect_to_host();
    }

    _socket.connectToHost(_serv_addr,_serv_port);
    if(_wait_for_connect)
    {
        _socket.waitForConnected(_wait_for_connect);
    }
}

void dt::BaseClient::disconnect_to_host()
{
    if(is_connected())
    {
        _socket.disconnectFromHost();
    }
}

bool dt::BaseClient::write_data(const QByteArray &data)
{
    if(is_connected() && !data.isEmpty())
    {
        //_socket.write(QByteArray::number(data.size()));
        _socket.write(data);
        return _wait_for_bytes_written ? _socket.waitForBytesWritten(_wait_for_bytes_written) : true;
    }
    return false;
}


bool dt::BaseClient::read_data(QByteArray &data)
{
    if(is_connected() && _socket.bytesAvailable())
    {
        data = _socket.readAll();
        return true;
    }
    return false;
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

QByteArray dt::BaseClient::IntToArray(qint32 source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

qint32 dt::BaseClient::ArrayToInt(QByteArray &temp)
{
    qint32 value = 0;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data >> value;
    return value;
}

dt::BaseClient::~BaseClient()
{
    if(is_connected())
    {
        disconnect_to_host();
    }
}

