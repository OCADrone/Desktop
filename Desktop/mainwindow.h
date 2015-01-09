#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>

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

public slots:
    void createNewModule(); /** Create a Module Object (added to the list). **/
    void deleteModule(); /** Destroy Module Object in list. **/
    void slotCloseTab(int index); /** Close Tab **/
};

#endif // MAINWINDOW_H
