#include "module.h"
#include <QLibrary>
#include <QFile>
#include <QFileInfo>

Module::Module()
{
    QDir dir;

    dir.setCurrent(dir.currentPath() + "/config");

    QString ini = QFileDialog::getOpenFileName();

    widget = NULL;
    name = "no name";
    module = "";

    QFile file(ini);

    QSettings* settings = new QSettings(ini, QSettings::IniFormat);
    if (settings->value("name").toString().size() > 0)
        name = settings->value("name").toString();
    if (settings->value("library").toString().size() > 0)
        module = QFileInfo(file).dir().absolutePath() + "/" + settings->value("library").toString();

    file.close();
    dir.setCurrent(dir.currentPath() + "/..");
    loadLibrary();
}

Module::~Module()
{
    delete widget;

    library->unload();
    delete library;

    delete actionDeleteModule;
}

void Module::loadLibrary()
{
    library = new QLibrary(module);
    if (!library->load()) {
        qDebug() << library->errorString();
        return;
    }
    typedef QWidget*(*ExecWidgetFunction)(void);
    ExecWidgetFunction ewf = (ExecWidgetFunction)library->resolve("exec");
    if (ewf)
        widget = ewf();
    else
        qDebug() << "Could not show widget from the loaded library";
}

void Module::deleteModule()
{
    emit moduleDeleted();
}

QAction *Module::getDeleteAction()
{
    return actionDeleteModule;
}

QString Module::getName() const
{
    return name;
}

QWidget *Module::getWidget() const
{
    return widget;
}
