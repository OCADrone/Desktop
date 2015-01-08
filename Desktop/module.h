#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QLibrary>
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QString>
#include <QAction>

/**
The Module Classe.
Herited from QObject.
Contains QWidget Object loaded.
**/
class Module : public QObject
{
    Q_OBJECT

public:
    Module();
    ~Module();
    void loadLibrary();
    QString getName() const; /** get the Module Name. **/
    QWidget *getWidget() const; /** get the complete QWidget. **/
    QAction *getDeleteAction(); /** Delete module. **/
    void unLoadLibrary(); /** Unload Library functions. **/

private:
    QLibrary    *library; /** Library to load for the 2 platforms. **/
    QString     module; /** Module path .dll or .so **/
    QString     name; /** Name displayed on the tab program. **/
    QWidget     *widget; /** Widget loaded. **/
    QAction     *actionDeleteModule; /** Destroy the module and the tab in program. **/

signals:
    void moduleDeleted();

public slots:
    void deleteModule();
};

#endif // MODULE_H
