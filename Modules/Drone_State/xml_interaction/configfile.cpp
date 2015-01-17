#include "configfile.h"

configFile::configFile(QWidget *parent) : QWidget(parent)
{

}

configFile::~configFile()
{
        std::map<QString, QString>::iterator it =
                element.find("id");
        element.erase(it, element.end());
}

void configFile::readFile(const QString &filepath)
{
    qDebug() << "file path: " << filepath;

    xmlFile = new QFile(filepath);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, QString("Load XML File Problem"),
                              QString("Couldn't open xmlfile.xml to load settings for download"),
                              QMessageBox::Ok);
    }
    xmlReader = new QXmlStreamReader(xmlFile);


    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {

            if(xmlReader->name() == "drone") { continue;}

            if(xmlReader->name() == "id")
                element.insert(std::pair<QString, QString>("id", xmlReader->readElementText()));
            else if(xmlReader->name() == "ip")
                element.insert(std::pair<QString, QString>("ip", xmlReader->readElementText()));
            else if(xmlReader->name() == "port")
                element.insert(std::pair<QString, QString>("port", xmlReader->readElementText()));
            else if(xmlReader->name() == "sshpath")
                element.insert(std::pair<QString, QString>("sshpath", xmlReader->readElementText()));
            else if(xmlReader->name() == "username")
                element.insert(std::pair<QString, QString>("username", xmlReader->readElementText()));
        }
    }

    if(xmlReader->hasError()) {
        QMessageBox::critical(this,
                              "xmlFile.xml Parse Error",xmlReader->errorString(),
                              QMessageBox::Ok);
        return;
    }
    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();
}

void configFile::createFile(QString name)
{
    QFile file("drone_" + name + ".xml");
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Drone");

    xmlWriter.writeTextElement("id", element["id"]);
    xmlWriter.writeTextElement("ip", element["ip"]);
    xmlWriter.writeTextElement("port", element["port"]);
    xmlWriter.writeTextElement("sshpath", element["sshpath"]);
    xmlWriter.writeTextElement("username", element["username"]);
    xmlWriter.writeEndElement();

    file.close();
}

void configFile::setElement(QString elem, QString name)
{
    element[elem] = name;
}

QString configFile::getElementByName(QString name)
{
    return (element[name]);
}
