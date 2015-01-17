#include "connexionmanager.h"

ConnectionManager::ConnectionManager(QString _hostname,
                                     QString _username,
                                     QString _key,
                                     QString _password,
                                     quint16 _port) :
                                     host(_hostname),
                                     username(_username),
                                     key (_key),
                                     password(_password),
                                     port(_port)
{
}

int ConnectionManager::Connection()
{
    connexion = new Sshconnexion;

    connexion->Connexion(host, username, key, password, port);

    return (0);
}

void ConnectionManager::splitCommand(QString command)
{
    QByteArray command_array(command.toStdString().c_str());

    connexion->sendCommand(command_array);
}

std::list<ConnectionManager::t_info*> ConnectionManager::getList() const
{
    return (dronelist);
}

int ConnectionManager::changeStatut(QString ip, int statut)
{
    foreach(t_info *i, dronelist)
        if (i->ip == ip) {
            i->statut = statut;
            return (0);
        }

    return (-1);
}

int ConnectionManager::getStatut(QString ip) const
{
    foreach(t_info *i, dronelist)
        if (i->ip == ip)
            return (i->statut);

    qDebug() << "Error: get Drone Statut failed.";
    return (-1);
}

int ConnectionManager::addDroneInList(QString ip, int statut)
{
    t_info *tmp = new t_info;

    tmp->ip = ip;
    tmp->statut = statut;
    dronelist.push_front(tmp); // throw exception bad_alloc

    return (0);
}

int ConnectionManager::deleteDroneInList(QString ip)
{
    foreach(t_info *i, dronelist)
        if (i->ip == ip) {
            dronelist.remove(i);
            return (0);
        }

    qDebug() << "Error: Delete Drone in List failed.";
    return (-1);
}
QString ConnectionManager::executeCommand(QByteArray command_array)
{
    connexion->sendCommand(command_array);
    return(connexion->getOutput());
}
