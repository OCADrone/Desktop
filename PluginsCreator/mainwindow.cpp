#include "mainwindow.h"
#include "ui_PluginsCreator.h"

PluginsCreator::PluginsCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PluginsCreator)
{
    ui->setupUi(this);
}

PluginsCreator::~PluginsCreator()
{
    delete ui;
}

void PluginsCreator::on_pluginsName_lineEdit_textChanged(const QString &arg1)
{
    ui->ClassName_lineEdit->setText(arg1);
}

void PluginsCreator::on_Quit_clicked()
{
    QCoreApplication::quit();
}

void PluginsCreator::on_Validate_clicked()
{
    QMessageBox s;

    s.setText("Dossier créé avec succès.\nmodules/"
              + ui->pluginsName_lineEdit->text());
    s.exec();
    QCoreApplication::quit();
}
