#include "configmanager.h"

configManager::configManager(QWidget *parent) : QWidget(parent)
{

}

configManager::~configManager()
{

}

configFile *configManager::getFile(QString path)
{
   QDir dir;

   configFile *tmp = new configFile(this);
   tmp->readFile((dir.currentPath()) + ("/") + path);

   return tmp;
}

QStringList configManager::getName() const
{
    return (filename);
}

void configManager::actualizeFileName(QString currentpath)
{
    QDir dir;

    dir.setCurrent(currentpath);

    if(!dir.exists("drone"))
        dir.mkdir("drone");
    dir.setCurrent(currentpath + "./drone");

    qDebug() << "PATH: " + dir.currentPath();

    filename = dir.entryList(QDir::Files,
                             QDir::Name);
}
