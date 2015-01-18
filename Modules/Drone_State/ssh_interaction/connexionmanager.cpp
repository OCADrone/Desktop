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

QString ConnectionManager::executeCommand(QByteArray command_array)
{
    connexion->sendCommand(command_array);
    return(connexion->getOutput());
}
