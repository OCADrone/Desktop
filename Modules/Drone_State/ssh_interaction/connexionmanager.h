#ifndef ConnectionManager_H
#define ConnectionManager_H

#include    <list>
#include    <QString>
#include    <QDebug>
#include    <QDir>

#include "sshconnexion.h"

class hardware_informations;

class ConnectionManager
{
public:
    ConnectionManager(QString, QString, QString, QString, quint16);
    virtual ~ConnectionManager() {}
    int Connection();
    void splitCommand(QString command);
    QString executeCommand(QByteArray command_array);
signals:

public slots:

private slots:

private:
    QString                                         host;
    QString                                         username;
    QString                                         key;
    QString                                         password;
    quint16                                         port;
    Sshconnexion                                    *connexion;
};

#endif // ConnectionManager_H
