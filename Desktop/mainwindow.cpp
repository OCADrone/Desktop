#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);

    server = new LocalSocketIpcServer("Desktop", parent);

    // QT connect

    connect(server, SIGNAL(messageReceived(QString)), this, SLOT(MessageToModule(QString)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)));

    // interface

    QDir myPath("modules");
    qDebug() << myPath.absolutePath();
    QFileInfoList fileList = myPath.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (QFileInfoList::Iterator it = fileList.begin(); it != fileList.end(); it++)
    {
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
    {
        ui->tabWidget->setCurrentIndex(ret);
    }
    else
    {
        qDebug() << "!Load Failed";
    }
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
        }
    }
    qDebug() << ui->tabWidget->count();
    for (int i = 0; i != ui->tabWidget->count(); i++)
    {
        qDebug() << i << "/" << ui->tabWidget->count();
    }
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::slotCloseTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::MessageToModule(QString message)
{
    qDebug() << "Desktop receive: " << message;
}

void MainWindow::on_pushButton_clicked()
{
    QString address("http://server.mine42.com/version.html");
    QMessageBox msgBox;
    QUrl url = address;
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString stringData(reply->readAll());

    if (ui->label->text().compare("Version du logiciel : " + stringData) == -1)
        msgBox.setText("Le logiciel est à jour.");
    else
        msgBox.setText("Le logiciel n'est pas à jour.\n"
                       "RDV sur wwww.ocadrone.com");

    msgBox.exec();
}

void MainWindow::on_actionActualiser_les_donn_es_triggered()
{

}
