#ifndef SSHCONNEXION_H
#define SSHCONNEXION_H

#include <QtDebug>
#include <QObject>
#include <QTextCodec>
/* to remove for final version */
#include <iostream>

#include "sftpchannel.h"
#include "sshconnection.h"
#include "sshremoteprocess.h"

class Sshconnexion : public QObject
{
    Q_OBJECT
public:

    explicit Sshconnexion(QObject *parent = 0);
    void Connexion(const QString &host,
                   const QString &username,
                   const QString &key,
                   const QString &password,
                   const quint16 &port);
    void sendCommand(QByteArray command);
    QString getOutput() const;

signals:

private slots:
    void onConnected();
    void onConnectionError(QSsh::SshError);
    void onChannelStarted();
    void readyReadStandardOutput();

private:
    QString                                     m_localFilename;
    QString                                     m_remoteFilename;
    QSsh::SftpChannel::Ptr                      m_channel;
    QSsh::SshConnection*                        m_connection;
    QSsh::SshRemoteProcess::Ptr                 remoteProc;
    QString                                     output;
};

#endif // SSHCONNEXION_H
