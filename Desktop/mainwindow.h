#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>

#include <localsocketipcserver.h>
#include "module.h"

namespace Ui {
class MainWindow;
}

/**
Principal Object who contains all the window and the mainly fonction as load a module.
**/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *getUi() const;

private:
    Ui::MainWindow *ui; /** UI object (form). **/
    QList<Module *> moduleList; /** Module list. **/
    LocalSocketIpcServer *server;
public slots:
    void createNewModule(); /** Create a Module Object (added to the list). **/
    void deleteModule(); /** Destroy Module Object in list. **/
    void slotCloseTab(int index); /** Close Tab **/
    void MessageToModule(QString);
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
