#include "mymodule.h"

MyModule::MyModule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyModule)
{
    ui->setupUi(this);
}
