#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include <QMap>
#include <QVector>
#include <QPair>
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
        void recved_data();

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

        QVector<QPair<QString,quint16>> info_connection();

        QList<QTcpSocket*> get_client_sockets() const;

        bool write_data(QTcpSocket *socket, QByteArray &data);
        bool write_data(int index, QByteArray &data);
        bool read_data(QTcpSocket *socket, QByteArray &data);

        void set_mutex(QMutex *mutex);
        void set_wait_for_bytes_written(int value);

        bool is_run()const;

        static QByteArray IntToArray(qint32 source);
        static qint32 ArrayToInt(QByteArray temp);

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
