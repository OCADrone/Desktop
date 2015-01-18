#ifndef DRONESTATE_H
#define DRONESTATE_H

#include <QWidget>
#include <QString>
#include <QCoreApplication>
#include <QStringList>
#include <iostream>
#include <QFileDialog>
#include <map>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include <QDir>

#include <iostream> // à enlever plus tard, ca me sert pour le debug

#include "ui_Drone_State.h"
#include "ssh_interaction/connexionmanager.h"
#include "xml_interaction/configmanager.h"
#include "module_interaction/localsocketipcclient.h"

#define DEFAULTSERVER "server.mine42.com"
#define DEFAULTPORT "2342"
#define DEFAULTUSER "guest"
#define DEFAULTPASSWD "guest"

/**
Contains the DroneState Form Widget.
Herited from QWidget.
**/
class DroneState : public QWidget
{
    Q_OBJECT
public:
    explicit        DroneState(QWidget *parent = 0);
    void            sendLog(const QString text); /** display text in log area **/
    void            setModuleList();

signals:

public slots:
    void            buttonStartPressed(); /** Start Drone Power Management. **/
    void            buttonConnectPressed(); /** SSH connection. **/
    void            buttonResetPressed(); /** Reset field **/

private slots:
    void            on_LoadPath_button_clicked();
    void            on_DroneChoice_comboBox_currentIndexChanged(const QString &arg1);
    void            on_SaveConfiguration_pushButton_clicked();
    void            on_Vider_clicked();
    void            on_Sauvegarder_clicked();
    void            on_refresh_pushButton_clicked();
    void            on_Hostname_textfield_textEdited(const QString &arg1);
    void            on_Port_textfield_textChanged(const QString &arg1);
    void            on_SSHKey_textfield_textChanged(const QString &arg1);
    void            on_Username_textfield_textChanged(const QString &arg1);
    void            on_DeveloperMode_checkBox_stateChanged(int arg1);
    void            on_prompt_pushButton_pressed();
    void            on_GetInformationsButton_clicked();

private:
    Ui::Drone_State                                *ui;
    QString                                        sshpath;
    QString                                        key;
    configManager                                  *configmanager;
    QString                                        log;
    QString                                        defaultdir;
    QStringList                                    choicexml;
    QDir                                           currentdir;
    ConnectionManager                              *manage;
    LocalSocketIpcClient                           *client;
    std::list<QString>                             *module;
};

#endif // DRONESTATE_H
