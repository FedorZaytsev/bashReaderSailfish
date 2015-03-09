#include "fileio.h"
#include <QFile>
#include <QTextStream>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{

    m_fpath = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)).filePath(QCoreApplication::applicationName());

    QDir dir(m_fpath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

QString FileIO::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(m_fpath+"/"+mSource);
    QString fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        t.setCodec("Windows-1251");
        do {
            line = t.readLine();
            fileContent += line;
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}

bool FileIO::exist()
{
    QFile file(m_fpath+"/"+mSource);
    bool exist = file.open(QIODevice::ReadOnly);
    file.close();
    return exist;
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(m_fpath+"/"+mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        qDebug()<<"Cannot open file"<<m_fpath+"/"+mSource;
        return false;
    }

    QTextStream out(&file);
    out.setCodec("Windows-1251");
    out << data;

    file.close();

    return true;
}
