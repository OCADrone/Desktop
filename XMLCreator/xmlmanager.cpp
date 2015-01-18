#include "xmlmanager.h"

XMLmanager::XMLmanager()
{
}

XMLmanager::~XMLmanager()
{

}

void XMLmanager::saveFile(QString xmlpath)
{
    xmlFile = new QFile(xmlpath + ".xml");
    if (!xmlFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Error on XML";
        return;
    }
    QTextStream ts(xmlFile);
    ts << final;
    xmlFile->close();

}

void XMLmanager::update(QString name, QStringList element)
{
    final = "";
    final += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    final += "<dronemodule>\n";
    final += "   <name>";
    final += name;
    final += "</name>\n";

    QStringList::iterator it;
    for (it = element.begin(); it != element.end();++it)
    {
        final += "   <data>";
        final += (*it);
        final += "</data>\n";
    }

    final += "</dronemodule>";
}

QString XMLmanager::getFinal() const
{
    return (final);
}
