#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myXML = new XMLmanager;
    modulename = tr("module sans nom");
    QStringList listModel;
    myXML->update(modulename, listModel);
    init();
}

void MainWindow::getData()
{
    // open file

    stringList = new QStringList;
    QFile textFile;

    QDir::setCurrent("../XMLCreator/data");
    textFile.setFileName("flight.ocadrone");
    qDebug() << "Path: " << QDir::currentPath();
    textFile.open(QIODevice::ReadOnly);
    QDir::setCurrent("../../");
    QTextStream textStream(&textFile);

    // get next line

    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
        {
            break;
        }
        else
        {
            stringList->append(line);
        }
    }
    textFile.close();
}

void MainWindow::init()
{
    // fill data from file

    getData();

    // set list with keyword

    QStringListModel *listModel = new QStringListModel(*stringList, NULL);
    listModel->setStringList(*stringList);
    ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView->setModel(listModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSauvegarder_triggered()
{
    // get items selection

    QModelIndexList list = ui->listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list)
    {
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    qDebug() << slist.join(",");

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save XML File"), modulename + ".xml",
        tr("XML OCADrone (*.xml);;All Files (*)"));

    // create / update XML File

    myXML->saveFile(modulename);
}

void MainWindow::on_refresh_clicked()
{
    ui->XMLvisualizer->clear();
    ui->XMLvisualizer->insertPlainText(myXML->getFinal());
}

void MainWindow::on_modulename_field_textChanged()
{
    if (ui->modulename_field->text().length() <= 3)
    {
        ui->messagefield->setText("<b>Veuiller Saisir au moins 3 caractères pour le nom de votre module !</b>");
    }
    else
    {
        ui->messagefield->setText("<b><font color='green'>Joli nom pour un module !</font></b>");
        modulename = ui->modulename_field->text();
    }
}

void MainWindow::on_addInformations_clicked()
{
    QModelIndexList selected = ui->listView->selectionModel()->selectedIndexes();

    QStringList list;

    foreach(QModelIndex index, selected)
    {
        list.append(index.data(Qt::DisplayRole ).toString());
    }
    myXML->update(modulename, list);
}
