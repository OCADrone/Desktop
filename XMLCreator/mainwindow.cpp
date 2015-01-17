#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList *stringList = new QStringList();
    stringList->append("ABC");
    stringList->append("123");

    QStringListModel *listModel = new QStringListModel(*stringList, NULL);
    listModel->setStringList(*stringList);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView->setModel(listModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
