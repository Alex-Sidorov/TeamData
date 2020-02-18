#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>

namespace DataTransfer
{
    class BaseClient : public QObject
    {
        Q_OBJECT

    signals:
        void socket_error(QAbstractSocket::SocketError state);
        void ready_data_read();
        void disconnected_socket();

    public:
        BaseClient(const QString &addr,quint16 port);
        virtual ~BaseClient();

        bool connect_to_host();
        void disconnect_to_host();

        bool write_data(QByteArray &data);
        bool read_data(QByteArray &data);

        void set_mutex(QMutex *mutex);
        void set_wait_for_bytes_written(int value);
        void set_wait_for_connect(int value);

    private:
        bool is_connected()const;

        QString _addr;
        quint16 _port;
        QTcpSocket  _socket;
        QMutex *_mutex;
        int _wait_for_bytes_written;
        int _wait_for_connect;
    };
}


#endif // CLIENT_H
