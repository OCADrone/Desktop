#include "sshconnexion.h"

#include <iostream>

Sshconnexion::Sshconnexion(QObject *parent) :
    QObject(parent), m_connection(0)
{
}

void Sshconnexion::Connexion(const QString &host,
                             const QString &username,
                             const QString &key,
                             const QString &password,
                             const quint16 &port)
{
    QSsh::SshConnectionParameters params;

    if (key.isEmpty())
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationByPassword;
    else {
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationByKey;
        params.privateKeyFile = key;
    }

    params.host = host;
    params.port = port;
    params.userName = username;
    params.password = password;

    params.timeout = 30;
    m_connection = new QSsh::SshConnection(params, this); // TODO free this pointer!

    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));

    qDebug() << "SshConnexion: Connecting to host" << host;

    m_connection->connectToHost();
}

void Sshconnexion::onConnected()
{
    qDebug() << "Sshconnexion: Connected";
}

void Sshconnexion::sendCommand(const QByteArray command_array)
{
        remoteProc = m_connection->createRemoteProcess(command_array);

        if(remoteProc){
            connect(remoteProc.data(),
                    SIGNAL(started()),
                    SLOT(onChannelStarted()));
            connect(remoteProc.data(),
                    SIGNAL(readyReadStandardOutput()),
                    SLOT(readyReadStandardOutput()));

            remoteProc->start();
        }
}

void Sshconnexion::onConnectionError(QSsh::SshError err)
{
    qDebug() << "Sshconnexion: Connection error" << err;
}

void Sshconnexion::onChannelStarted(){
    qDebug() << "COM: Channel Started";
}

void Sshconnexion::readyReadStandardOutput()
{
    qDebug() << remoteProc->readAll();
}

QString Sshconnexion::getOutput() const
{
    return (output);
}
