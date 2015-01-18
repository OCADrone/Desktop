#ifndef LOCALSOCKETIPCCLIENT_H
#define LOCALSOCKETIPCCLIENT_H
#include <QtNetwork/QLocalSocket>

class LocalSocketIpcClient : public QObject
{
    Q_OBJECT
public:
    typedef struct s_info
    {
        int                                         id;
        QString                                     name;
        std::list<QString>                          data;
    }t_info;
    LocalSocketIpcClient(QString remoteServername, QObject *parent = 0);
    ~LocalSocketIpcClient();
signals:

public slots:
    void send_MessageToServer(QString);

    void socket_connected();
    void socket_disconnected();

    void socket_readReady();
    void socket_error(QLocalSocket::LocalSocketError);

private:
    QLocalSocket*   m_socket;
    quint16 m_blockSize;
    QString m_message;
    QString m_serverName;
};

#endif // LOCALSOCKETIPCCLIENT_H
