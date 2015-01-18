#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>

namespace Ui
{
class MainWindow;
}

class MainWindow :      public QMainWindow
{
    Q_OBJECT

public:
    explicit            MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void                on_ocadronedeskrop_clicked();
    void                on_createmodule_clicked();
    void                on_xmlcreator_clicked();
    void                on_website_clicked();

private:
    Ui::MainWindow      *ui;
};

#endif // MAINWINDOW_H
