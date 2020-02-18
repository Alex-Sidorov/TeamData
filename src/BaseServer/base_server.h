#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QMap>
#include <QSharedPointer>

namespace DataTransfer
{
    class BaseServer : public QObject
    {
        Q_OBJECT

    signals:
        void new_connection();
        void socket_error(QTcpSocket *socket, QAbstractSocket::SocketError state);
        void ready_data_read(QTcpSocket *socket);
        void disconnected_socket(QTcpSocket *socket);

    public:
        BaseServer(const QString &addr,quint16 port);
        BaseServer(const BaseServer&) = delete;
        BaseServer(const BaseServer&&) = delete;
        BaseServer& operator=(const BaseServer&) = delete;
        BaseServer& operator=(const BaseServer&&) = delete;
        virtual ~BaseServer();

        bool run();
        void stop();

        void add_connection();
        void remove_connection(int index);
        void remove_connection(QTcpSocket *socket);

        bool write_data(QTcpSocket *socket, QByteArray &data);
        bool read_data(QTcpSocket *socket, QByteArray &data);

        void set_mutex(QMutex *mutex);
        void set_wait_for_bytes_written(int value);

    private:
        bool is_valid_socket(QTcpSocket*) const;

        QString _addr;
        quint16 _port;
        QTcpServer _server;
        QList<QTcpSocket*>  _sockets;
        QMap<QTcpSocket*,QSharedPointer<QMutex>> _sockets_mutexes;
        QMutex *_mutex;
        int _wait_for_bytes_written;
    };
}



#endif // SERVER_H
