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
    typedef                     struct s_info
    {
        int                     statut;
        QString                 ip;
    }                           t_info;
    ConnectionManager(QString, QString, QString, QString, quint16);
    virtual ~ConnectionManager() {}
    int Connection();
    std::list<ConnectionManager::t_info*> getList() const;
    int changeStatut(QString ip, int statut);
    int getStatut(QString ip) const;
    int addDroneInList(QString ip, int statut);
    int deleteDroneInList(QString ip);
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
    std::list<ConnectionManager::t_info*>           dronelist;
    Sshconnexion                                    *connexion;
};

#endif // ConnectionManager_H
