#include "localsocketipcserver.h"

LocalSocketIpcServer::LocalSocketIpcServer(QString servername, QObject *parent)
    :QObject(parent)
{
    m_server = new QLocalServer(this);
    if (!m_server->listen(servername)) {
        qDebug() << "Not able to start the Server";
    }

    connect(m_server, SIGNAL(newConnection()), this, SLOT(socket_new_connection()));
}

LocalSocketIpcServer::~LocalSocketIpcServer()
{

}

void LocalSocketIpcServer::socket_new_connection()
{
    QLocalSocket *clientConnection = m_server->nextPendingConnection();

    while (clientConnection->bytesAvailable() < (int)sizeof(quint32))
        clientConnection->waitForReadyRead();


    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);
    if (clientConnection->bytesAvailable() < (int)sizeof(quint16)) {
        return;
    }
    QString message;
    in >> message;

    qDebug() << message;

    emit messageReceived(message);
}
