#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QIODevice>
#include <QWidget>
#include <map>

class configFile : public QWidget
{
public:
   configFile(QWidget *parent = 0);
   virtual ~configFile();
   void readFile(const QString &filepath);
   void createFile(QString name);
   void setElement(QString elem, QString name);
   QString getElementByName(QString name);
signals:

public slots:

private slots:

private:
   QXmlStreamReader             *xmlReader;
   QFile                        *xmlFile;
   std::map<QString, QString>   element;
};

#endif // CONFIGFILE_H
