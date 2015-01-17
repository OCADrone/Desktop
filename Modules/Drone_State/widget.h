#include <QtGui>

#if defined DRONE_STATE
    #define DRONE_STATE_COMMON_DLLSPEC Q_DECL_EXPORT
#else
    #define DRONE_STATE_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

extern "C" DRONE_STATE_COMMON_DLLSPEC QWidget* exec();
