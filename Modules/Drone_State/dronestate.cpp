#include "dronestate.h"

DroneState::DroneState(QWidget *parent) :
    QWidget(parent)
{   
    /* Enable or disable default button */

    configmanager = new configManager(this);

    ui = new Ui::Drone_State;
    ui->setupUi(this);

    /* Developer mode default disabled */

    ui->command_label->setVisible(false);
    ui->prompt_lineEdit->setVisible(false);
    ui->prompt_pushButton->setVisible(false);

    /* Log */

    sendLog(tr("<b>Démarrage des logs.</b>"));

    /* set default field */

    ui->Hostname_textfield->setText(DEFAULTSERVER);
    ui->Port_textfield->setText(DEFAULTPORT);
    ui->Username_textfield->setText(DEFAULTUSER);
    ui->Password_textfield->setText(DEFAULTPASSWD);

    /* Set default directory */

    currentdir.setCurrent(currentdir.currentPath() +
                          "/../../OCADrone_Desktop");
    defaultdir = currentdir.currentPath();

    /* Dropdown Choice xml file list */

    configmanager->actualizeFileName(defaultdir);
    choicexml = configmanager->getName();
    choicexml.push_front("");
    ui->DroneChoice_comboBox->addItems(choicexml);

    /* Connect button */

    connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(buttonConnectPressed()));
    connect(ui->buttonReset, SIGNAL(clicked()), this, SLOT(buttonResetPressed()));

    sendLog(tr("Chargement du module <b>[OK]</b>."));

    /* Client */

    client = new LocalSocketIpcClient("Desktop", parent);
    setModuleList();
}

void DroneState::setModuleList()
{
    /* Set Module list*/

    int i;
    currentdir.setCurrent(defaultdir);
    QStringList filter("*.xml");
    QDir myDir("xml");
    QStringList filesList = myDir.entryList(QStringList(filter), QDir::Files);
    currentdir.setCurrent(currentdir.currentPath() + "/xml");
    QStringList::iterator it;

    i = 0;
    for (it = filesList.begin(); it != filesList.end();++it)
    {
        QFile file(*it);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "File open error:" << file.errorString();
            return;
        }
        LocalSocketIpcClient::t_info *myModule = new LocalSocketIpcClient::t_info;

        myModule->id = i;
        QXmlStreamReader inputStream(&file);
        while (!inputStream.atEnd() && !inputStream.hasError())
        {
            inputStream.readNext();
            if (inputStream.isStartElement())
            {
                QString name = inputStream.name().toString();
                if(name == "name")
                {
                    QLabel *label = new QLabel(inputStream.readElementText());
                    QVBoxLayout *box = new QVBoxLayout;
                    box->addWidget(label);
                    ui->Informations->addLayout(box);
                    myModule->name = name;
                }
                else if(name == "data")
                {
                    myModule->data.push_back(inputStream.readElementText());
                }
            }
        }
        module->push_back(myModule);
        i++;
        file.close();
    }
   // client->send_MessageToServer(module);
    client->send_MessageToServer("Hello world");
}

void DroneState::buttonStartPressed()
{
    QMessageBox::information(this, "Drone State Warning", "How are you ?");
}

void DroneState::buttonConnectPressed()
{ 
    /* Connection Manager */

    sendLog(tr("Initialisation de la connexion ..."));

    manage = new ConnectionManager(ui->Hostname_textfield->text(),          // Host
                                   ui->Username_textfield->text(),          // Username
                                   ui->SSHKey_textfield->text(),            // RSA Key
                                   ui->Password_textfield->text(),          // password
                                   ui->Port_textfield->text().toShort());   //Port

    manage->Connection();
    sendLog(tr("Initialisation connexion <b>[OK]</b>."));

    sendLog(tr("Vous avez désormais accès à la récuperation des informations !"));

    ui->getInfo_progressBar->setDisabled(false);
    ui->GetInformationsButton->setDisabled(false);
}

void DroneState::buttonResetPressed()
{
    /* Reset field */

    ui->Hostname_textfield->setText("");
    ui->Username_textfield->setText("");
}

void DroneState::on_LoadPath_button_clicked()
{
    /* Load default path */

    currentdir.setCurrent(defaultdir + "/..");

    /* browse */

    sshpath = QFileDialog::getOpenFileName();
    ui->SSHKey_textfield->setText(sshpath);
}

void DroneState::sendLog(const QString text)
{
    ui->LogHistory_textfield->setHtml(log += text + "<br>");
}

void DroneState::on_DroneChoice_comboBox_currentIndexChanged(const QString &arg1)
{
    /* skip if default string */

    if (!arg1.compare(""))
        return;

    /* skip if saved name */

    if (arg1 == ui->save_textfield->text())
        return;

    sendLog(tr("Chargement des informations du fichier ..."));

    // currentdir.setCurrent(defaultdir + "/config");

    configFile *load = configmanager->getFile(arg1);

    ui->Hostname_textfield->setText(load->getElementByName("ip"));
    ui->Port_textfield->setText(load->getElementByName("port"));
    ui->SSHKey_textfield->setText(load->getElementByName("sshpath"));
    ui->Username_textfield->setText(load->getElementByName("username"));

    ui->loadedfilename_label->setText(arg1);

    sendLog(tr("Chargement des informations de connexion <b>[OK]</b>"));

    QFile checksshpath(load->getElementByName("sshpath"));

    QPalette palette = ui->SSHKey_textfield->palette();

    if(!checksshpath.exists())
    {
        palette.setColor(QPalette::Text, QColor(255,0,0));
        ui->SSHKey_textfield->setPalette(palette);
        sendLog("<font color=\"red\">Attention: le fichier de la clé SSH n'existe pas.</font>");
    }
    else
    {
        palette.setColor(QPalette::Text, QColor(0,0,0));
        ui->SSHKey_textfield->setPalette(palette);
    }

    /* reset default dir */

    currentdir.setCurrent(defaultdir);
}

void DroneState::on_SaveConfiguration_pushButton_clicked()
{
    sendLog(tr("Sauvegarde des informations de connexion en cours ..."));

    configFile *save = new configFile(this);

    /* Set data from field */

    save->setElement("ip", ui->Hostname_textfield->text());
    save->setElement("port", ui->Port_textfield->text());
    save->setElement("sshpath", ui->SSHKey_textfield->text());
    save->setElement("username", ui->Username_textfield->text());

    /* creating file */

    // currentdir.setCurrent(defaultdir + "/config");

    save->createFile(ui->save_textfield->text());

    ui->DroneChoice_comboBox->addItem("drone_" + ui->save_textfield->text() + ".xml");
    int index = ui->DroneChoice_comboBox->findText("drone_" +
                                                   ui->save_textfield->text() +
                                                   ".xml");
    ui->DroneChoice_comboBox->setCurrentIndex(index);

    sendLog(tr("Sauvegarde des informations de connexion <b>[OK]</b>"));

    currentdir.setCurrent(defaultdir);
}

void DroneState::on_Vider_clicked()
{
    if (log == "<b>Démarrage des logs.</b><br>")
    {
        QMessageBox::question(this, tr("Vider le contenu"),
                              tr("Les Logs ont déjà été vidés."),
                              QMessageBox::Ok);
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Vider le contenu"),
                                  tr("Êtes-vous sûr de vouloir vider les logs?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        log = "<b>Démarrage des logs.</b>";
        sendLog("");
    }
}

void DroneState::on_Sauvegarder_clicked()
{

}

void DroneState::on_refresh_pushButton_clicked()
{
    sendLog(tr("Actualisation des informations de connexion du fichier ...")
            + ui->DroneChoice_comboBox->currentText());
    emit on_DroneChoice_comboBox_currentIndexChanged(ui->DroneChoice_comboBox->currentText());
    sendLog(tr("Actualisation des informations de connexion <b>[OK]</b>"));
}

void DroneState::on_Hostname_textfield_textEdited(const QString &arg1)
{
    static_cast<void>(arg1);
    ui->loadedfilename_label->setText(tr("Aucun"));
}

void DroneState::on_Port_textfield_textChanged(const QString &arg1)
{
    static_cast<void>(arg1);
    ui->loadedfilename_label->setText(tr("Aucun"));
}

void DroneState::on_SSHKey_textfield_textChanged(const QString &arg1)
{
    static_cast<void>(arg1);
    ui->loadedfilename_label->setText(tr("Aucun"));
}

void DroneState::on_Username_textfield_textChanged(const QString &arg1)
{
    static_cast<void>(arg1);
    ui->loadedfilename_label->setText(tr("Aucun"));
}

void DroneState::on_DeveloperMode_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        ui->command_label->setVisible(true);
        ui->prompt_lineEdit->setVisible(true);
        ui->prompt_pushButton->setVisible(true);
    }
    else
    {
        ui->command_label->setVisible(false);
        ui->prompt_lineEdit->setVisible(false);
        ui->prompt_pushButton->setVisible(false);
    }
}

void DroneState::on_prompt_pushButton_pressed()
{
    manage->splitCommand(ui->prompt_lineEdit->text());
}

void DroneState::on_GetInformationsButton_clicked()
{
    // client->send_MessageToServer("Bonjour Desktop");
}
