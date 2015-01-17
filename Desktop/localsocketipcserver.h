#ifndef LOCALSOCKETIPCCLIENT_H
#define LOCALSOCKETIPCCLIENT_H
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

class LocalSocketIpcServer : public QObject
{
    Q_OBJECT
public:
    LocalSocketIpcServer(QString servername, QObject *parent);
    ~LocalSocketIpcServer();

signals:
    void messageReceived(QString);

public slots:
    void socket_new_connection();

private:
    QLocalServer*       m_server;
};

#endif // LOCALSOCKETIPCCLIENT_H
