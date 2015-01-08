#include <QObject>
#include <QApplication>
#include <QFile>
#include <QFileDialog>

#include "mainwindow.h"
#include "modulehandler.h"
#include "ui_mainwindow.h"

void initConnects(MainWindow *w, ModuleHandler* m)
{
    QObject::connect(w->getUi()->actionChargerModule, SIGNAL(triggered()), m, SLOT(newModule()));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    ModuleHandler m(w.getUi());
    initConnects(&w, &m);

    return a.exec();
}
