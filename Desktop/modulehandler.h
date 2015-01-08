#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <QObject>

#include "ui_mainwindow.h"
#include "module.h"

/**
Class to create new Module.
**/
class ModuleHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModuleHandler(Ui::MainWindow *ui, QObject *parent = 0);

private:
    QList<Module *> modulesList;
    Ui::MainWindow *ui;

signals:

public slots:
    void newModule();
};

#endif // MODULEHANDLER_H
