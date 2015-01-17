#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QDir>
#include <QStringList>
#include <iostream>
#include <QWidget>

#include "configfile.h"

class configManager : public QWidget
{
public:
    configManager(QWidget *parent = 0);
    virtual ~configManager();
    void actualizeFileName(QString currentpath);
    configFile *getFile(QString path);
    QStringList getName() const;
signals:

public slots:

private slots:

private:
    std::list<configFile*> filelist;
    QStringList            filename;
};

#endif // CONFIGMANAGER_H
