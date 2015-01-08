#include "modulehandler.h"

ModuleHandler::ModuleHandler(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
}

void ModuleHandler::newModule()
{
    Module *m = new Module;

    modulesList.push_back(m);

    int ret = ui->tabWidget->addTab(m->getWidget(), m->getName());
    if (ret >= 0)
        ui->tabWidget->setCurrentIndex(ret);
    else
        qDebug() << "Failed to load";
}
