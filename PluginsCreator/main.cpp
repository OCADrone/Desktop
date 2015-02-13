#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PluginsCreator w;
    w.setWindowTitle("PluginsCreator");
    w.show();

    return a.exec();
}
