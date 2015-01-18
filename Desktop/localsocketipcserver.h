#ifndef LOCALSOCKETIPCCLIENT_H
#define LOCALSOCKETIPCCLIENT_H
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

class LocalSocketIpcServer : public QObject
{
    Q_OBJECT
public:
    typedef struct s_info
    {
        int                                         id;
        QString                                     name;
        std::list<QString>                          data;
    }t_info;
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
