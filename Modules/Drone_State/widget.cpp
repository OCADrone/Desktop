#include <QtGui>

#include "widget.h"
#include "dronestate.h"

QWidget* exec()
{
    DroneState *widget = new DroneState();
    return widget;
}
