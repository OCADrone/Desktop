#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class PluginsCreator;
}

class PluginsCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PluginsCreator(QWidget *parent = 0);
    ~PluginsCreator();

private slots:
    void on_pluginsName_lineEdit_textChanged(const QString &arg1);

    void on_Quit_clicked();

    void on_Validate_clicked();

private:
    Ui::PluginsCreator *ui;
};

#endif // MAINWINDOW_H
