#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MODULES_PATH "debug/modules"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    connect(ui->actionCharger_module, SIGNAL(triggered()), this, SLOT(createNewModule()));
//    ui->actionCharger_module->triggered();

    ui->tabWidget->setTabsClosable(true);
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));

    QDir test("modules");
    qDebug() << test.absolutePath();
//    QStringList filters;
//    filters << ".ini";
//    test.setNameFilters(filters);
    QFileInfoList fileList = test.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList::Iterator it;
    for (QFileInfoList::Iterator it = fileList.begin(); it != fileList.end(); it++) {
        QDir currentDir((*it).absoluteFilePath());
        currentDir.setNameFilters(QStringList("*.ini"));
        qDebug() << currentDir.absolutePath() << currentDir.count();
        QFileInfoList currentDirList = currentDir.entryInfoList(QDir::Files);
        for (QFileInfoList::Iterator itd = currentDirList.begin(); itd != currentDirList.end(); itd++) {
            qDebug() << (*it).absoluteFilePath();
        }
    }
}

MainWindow::~MainWindow()
{
    moduleList.clear();
    delete ui;
}

void MainWindow::createNewModule()
{
    Module *newmodule = new Module();

    moduleList.push_back(newmodule);
    int ret = ui->tabWidget->addTab(newmodule->getWidget(), newmodule->getName());
    if (ret >= 0)
        ui->tabWidget->setCurrentIndex(ret);
    else
        qDebug() << "!Load Failed";
//    QMenu *newmenu = ui->menuMOdules->addMenu(newmodule->getName());
//    newmenu->addAction(newmodule->getDeleteAction());
//    connect(newmodule, SIGNAL(moduleDeleted()), this, SLOT(deleteModule()));
}

void MainWindow::deleteModule()
{
    QList<Module *>::Iterator it;

    for (it = moduleList.begin(); it != moduleList.end(); it++)
    {
        qDebug() << (*it) << "/" << QObject::sender();
        if (QObject::sender() == (*it))
        {
            qDebug() << "Module in list !";
            //delete QObject::sender();
        }
    }
    qDebug() << ui->tabWidget->count();
    for (int i = 0; i != ui->tabWidget->count(); i++)
        qDebug() << i << "/" << ui->tabWidget->count();
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::slotCloseTab(int index)
{
    ui->tabWidget->removeTab(index);
}
