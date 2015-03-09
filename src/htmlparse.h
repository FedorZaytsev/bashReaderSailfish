#ifndef HTMLPARSE_H
#define HTMLPARSE_H

#include <QObject>
#include <QVector>
#include <QtQuick>

struct bashQuote {
    QString id;
    QString rating;
    QString date;
    QString text;
    QString rate_key;
    int pageID;
};

class HTMLParse : public QObject
{
    Q_OBJECT
public:
    explicit HTMLParse(QObject *parent = 0);
    virtual ~HTMLParse();
    Q_INVOKABLE void parseEng(QString str);
    Q_INVOKABLE void parseRu(QString str);
    Q_INVOKABLE int count();
    Q_INVOKABLE QString text(int id);
    Q_INVOKABLE QString id(int id);
    Q_INVOKABLE QString rating(int id);
    Q_INVOKABLE QString date(int id);
    Q_INVOKABLE QString wantMore();
    Q_INVOKABLE QString rate_key(int id);


signals:
    void finished(QString data);
public slots:
    void replyFinished(QNetworkReply*);


private:
    QVector<struct bashQuote> m_data;
    QString m_nextPage;
    QProcess* proc;
};

#endif // HTMLPARSE_H
