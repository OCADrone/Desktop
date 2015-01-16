#include "widget.h"
#include "mymodule.h"

QWidget* exec()
{
    MyModule *widget = new MyModule;
    return widget;
}
