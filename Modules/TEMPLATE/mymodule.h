#ifndef HARDWARE_H
#define HARDWARE_H

#include <QWidget>
#include <QDebug>

#include "module_name.h"

#include "ui_Form.h"

/**
Contains Form.
Herited from QWidget.
**/
class                       MyModule : public QWidget
{
    Q_OBJECT
public:
    explicit                MyModule(QWidget *parent = 0);

signals:

public slots:

private:
    Ui::MyModule            *ui;

};

#endif // HARDWARE_H
