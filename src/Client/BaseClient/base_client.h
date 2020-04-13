#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

namespace DataTransfer
{
    class BaseClient : public QObject
    {
        Q_OBJECT

    signals:
        void socket_error(QAbstractSocket::SocketError state);
        void ready_data_read();
        void connected_socket();
        void disconnected_socket();
        void recved_data();

    public:
        BaseClient(const QString &addr,quint16 port);
        virtual ~BaseClient();

        void connect_to_host();
        void disconnect_to_host();

        bool write_data(QByteArray &data);
        bool read_data(QByteArray &data);

        void set_wait_for_bytes_written(int value);
        void set_wait_for_connect(int value);

        bool is_connected()const;

        static QByteArray IntToArray(qint32 source);
        static qint32 ArrayToInt(QByteArray &temp);
    private:

        QString _addr;
        quint16 _port;
        QTcpSocket  _socket;
        int _wait_for_bytes_written;
        int _wait_for_connect;
    };
}


#endif // CLIENT_H
