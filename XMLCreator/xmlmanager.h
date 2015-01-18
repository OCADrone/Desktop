#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

class XMLmanager
{
public:
    XMLmanager();
    ~XMLmanager();
    void saveFile(QString xmlpath);
    void update(QString name, QStringList element);
    QString getFinal() const;
private:
    QXmlStreamReader             *xmlReader;
    QFile                        *xmlFile;
    QString                      final;
};

#endif // XMLMANAGER_H
