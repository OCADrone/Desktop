#include <QtGui>
#include <QObject>
#include "mymodule.h"

#if defined HARDWARE_INFORMATIONS
    #define HARDWARE_INFORMATIONS_COMMON_DLLSPEC Q_DECL_EXPORT
#else
    #define HARDWARE_INFORMATIONS_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

extern "C" HARDWARE_INFORMATIONS_COMMON_DLLSPEC QWidget* exec();
