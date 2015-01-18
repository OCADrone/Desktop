#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QModelIndexList>
#include <QDir>
#include <QFileDialog>
#include <QModelIndexList>
#include <QDebug>

#include "xmlmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow :          public QMainWindow
{
    Q_OBJECT

public:
    explicit                MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void                    init();
    void                    getData();

private slots:

    void                    on_actionSauvegarder_triggered();
    void                    on_modulename_field_textChanged();
    void                    on_addInformations_clicked();

private:
    Ui::MainWindow          *ui;
    QString                 modulename;
    QStringList             *stringList;
    XMLmanager *myXML;
};

#endif // MAINWINDOW_H
