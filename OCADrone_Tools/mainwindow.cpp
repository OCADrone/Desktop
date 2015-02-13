#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("OCADrone Tools");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ocadronedeskrop_clicked()
{
    QString program = "OCADrone_Desktop.exe";
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, 0);
}

void MainWindow::on_createmodule_clicked()
{
    QString program = "PluginsCreator.exe";
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, 0);
}

void MainWindow::on_xmlcreator_clicked()
{
    QString program = "XMLCreator.exe";
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, 0);
}

void MainWindow::on_website_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.ocadrone.com"));
}
