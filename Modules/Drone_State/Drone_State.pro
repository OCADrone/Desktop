greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

QT += core network

# CONFIG += staticlib

# Defines

DEFINES += QSSH_LIBRARY
DEFINES += DRONE_STATE

# Useful for wrong default configuration from QT5

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

# Botan configuration

PRECOMPILED_HEADER = Qssh/3rdparty/precompiled_headers/botan_pch.h

# Botan configuration

CONFIG += exceptions

# Include

INCLUDEPATH += $$PWD/Qssh/ssh/
INCLUDEPATH += $$PWD/Qssh/3rdparty/
INCLUDEPATH += $$PWD/mod/

HEADERS += \
    Qssh/ssh/sshsendfacility_p.h \ # Qssh
    Qssh/ssh/sshremoteprocess.h \
    Qssh/ssh/sshremoteprocess_p.h \
    Qssh/ssh/sshpacketparser_p.h \
    Qssh/ssh/sshpacket_p.h \
    Qssh/ssh/sshoutgoingpacket_p.h \
    Qssh/ssh/sshkeygenerator.h \
    Qssh/ssh/sshkeyexchange_p.h \
    Qssh/ssh/sshincomingpacket_p.h \
    Qssh/ssh/sshexception_p.h \
    Qssh/ssh/ssherrors.h \
    Qssh/ssh/sshcryptofacility_p.h \
    Qssh/ssh/sshconnection.h \
    Qssh/ssh/sshconnection_p.h \
    Qssh/ssh/sshchannelmanager_p.h \
    Qssh/ssh/sshchannel_p.h \
    Qssh/ssh/sshcapabilities_p.h \
    Qssh/ssh/sshbotanconversions_p.h \
    Qssh/ssh/sftppacket_p.h \
    Qssh/ssh/sftpoutgoingpacket_p.h \
    Qssh/ssh/sftpoperation_p.h \
    Qssh/ssh/sftpincomingpacket_p.h \
    Qssh/ssh/sftpdefs.h \
    Qssh/ssh/sftpchannel.h \
    Qssh/ssh/sftpchannel_p.h \
    Qssh/ssh/sshremoteprocessrunner.h \
    Qssh/ssh/sshconnectionmanager.h \
    Qssh/ssh/sshpseudoterminal.h \
    Qssh/ssh/sshkeypasswordretriever_p.h \
    Qssh/ssh/sftpfilesystemmodel.h \
    Qssh/ssh/ssh_global.h \
    Qssh/3rdparty/botan/botan.h \ # Botan
    widget.h \ # Drone_State
    dronestate.h \
    paths.hh \
    module_interaction/localsocketipcclient.h \
    ssh_interaction/sshconnexion.h \
    ssh_interaction/connexionmanager.h \
    xml_interaction/configmanager.h \
    xml_interaction/configfile.h

SOURCES += \
    Qssh/ssh/sshsendfacility.cpp \ # Qssh
    Qssh/ssh/sshremoteprocess.cpp \
    Qssh/ssh/sshpacketparser.cpp \
    Qssh/ssh/sshpacket.cpp \
    Qssh/ssh/sshoutgoingpacket.cpp \
    Qssh/ssh/sshkeygenerator.cpp \
    Qssh/ssh/sshkeyexchange.cpp \
    Qssh/ssh/sshincomingpacket.cpp \
    Qssh/ssh/sshcryptofacility.cpp \
    Qssh/ssh/sshconnection.cpp \
    Qssh/ssh/sshchannelmanager.cpp \
    Qssh/ssh/sshchannel.cpp \
    Qssh/ssh/sshcapabilities.cpp \
    Qssh/ssh/sftppacket.cpp \
    Qssh/ssh/sftpoutgoingpacket.cpp \
    Qssh/ssh/sftpoperation.cpp \
    Qssh/ssh/sftpincomingpacket.cpp \
    Qssh/ssh/sftpdefs.cpp \
    Qssh/ssh/sftpchannel.cpp \
    Qssh/ssh/sshremoteprocessrunner.cpp \
    Qssh/ssh/sshconnectionmanager.cpp \
    Qssh/ssh/sshkeypasswordretriever.cpp \
    Qssh/ssh/sftpfilesystemmodel.cpp \
    Qssh/3rdparty/botan/botan.cpp \  # Botan
    \             # configmanager.cpp # Drone_State
    widget.cpp \
    dronestate.cpp \
    module_interaction/localsocketipcclient.cpp \
    ssh_interaction/connexionmanager.cpp \
    ssh_interaction/sshconnexion.cpp \
    xml_interaction/configmanager.cpp \
    xml_interaction/configfile.cpp

# Form UI

FORMS += \
    Drone_State.ui

# Botan configuration

DEFINES += BOTAN_DLL=Q_DECL_EXPORT
unix:DEFINES += BOTAN_TARGET_OS_HAS_GETTIMEOFDAY BOTAN_HAS_ALLOC_MMAP \
    BOTAN_HAS_ENTROPY_SRC_DEV_RANDOM BOTAN_HAS_ENTROPY_SRC_EGD BOTAN_HAS_ENTROPY_SRC_FTW \
    BOTAN_HAS_ENTROPY_SRC_UNIX BOTAN_HAS_MUTEX_PTHREAD BOTAN_HAS_PIPE_UNIXFD_IO
*linux*:DEFINES += BOTAN_TARGET_OS_IS_LINUX BOTAN_TARGET_OS_HAS_CLOCK_GETTIME \
    BOTAN_TARGET_OS_HAS_DLOPEN BOTAN_TARGET_OS_HAS_GMTIME_R BOTAN_TARGET_OS_HAS_POSIX_MLOCK \
    BOTAN_HAS_DYNAMICALLY_LOADED_ENGINE BOTAN_HAS_DYNAMIC_LOADER
macx:DEFINES += BOTAN_TARGET_OS_IS_DARWIN
*g++*:DEFINES += BOTAN_BUILD_COMPILER_IS_GCC
*clang*:DEFINES += BOTAN_BUILD_COMPILER_IS_CLANG
*icc*:DEFINES += BOTAN_BUILD_COMPILER_IS_INTEL

win32 {
    DEFINES += BOTAN_TARGET_OS_IS_WINDOWS \
        BOTAN_TARGET_OS_HAS_LOADLIBRARY BOTAN_TARGET_OS_HAS_WIN32_GET_SYSTEMTIME \
        BOTAN_TARGET_OS_HAS_WIN32_VIRTUAL_LOCK BOTAN_HAS_DYNAMICALLY_LOADED_ENGINE \
        BOTAN_HAS_DYNAMIC_LOADER BOTAN_HAS_ENTROPY_SRC_CAPI BOTAN_HAS_ENTROPY_SRC_WIN32 \
        BOTAN_HAS_MUTEX_WIN32

    win32-msvc* {
        QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250
        DEFINES += BOTAN_BUILD_COMPILER_IS_MSVC BOTAN_TARGET_OS_HAS_GMTIME_S
    } else {
        QMAKE_CFLAGS += -fpermissive -finline-functions -Wno-long-long
        QMAKE_CXXFLAGS += -fpermissive -finline-functions -Wno-long-long
    }
    LIBS += -ladvapi32 -luser32
}

unix:*-g++* {
    QMAKE_CFLAGS += -fPIC -ansi -fpermissive -finline-functions -Wno-long-long
    QMAKE_CXXFLAGS += -fPIC -ansi -fpermissive -finline-functions -Wno-long-long
    QMAKE_CXXFLAGS_HIDESYMS -= -fvisibility-inlines-hidden # for ubuntu 7.04
}

linux*|freebsd* {
    LIBS += -lrt
}

# End of Botan configuration

RESOURCES += \
    myResource.qrc
