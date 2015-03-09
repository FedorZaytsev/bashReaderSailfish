#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QtQuick>
#include "curlproxy.h"


class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);
    ~Storage();
    Q_INVOKABLE void changleLang();
    Q_INVOKABLE QString lang() {return m_lang;}
    Q_INVOKABLE void loadStorage();
    Q_INVOKABLE void saveAll();
    Q_INVOKABLE void addRatedRU(unsigned int id);
    Q_INVOKABLE bool isRatedRU(unsigned int id);
    Q_INVOKABLE void addRatedENG(unsigned int id);
    Q_INVOKABLE bool isRatedENG(unsigned int id);
    Q_INVOKABLE void rateLaterRU(QVariant ident, QVariant action, QVariant idx);
    Q_INVOKABLE void rateLaterENG(QVariant url);
    Q_INVOKABLE int rateSize() {return m_rateLater.size();}
    Q_INVOKABLE QString rateUrl(int idx);
    Q_INVOKABLE void deleteRateElement(int id);
    Q_INVOKABLE void rateRU(QVariant, QVariant);


    CurlProxy *proxy() const;
    void setProxy(CurlProxy *proxy);

signals:

public slots:

private:
    QString m_lang;
    QString m_fpath;
    QVector<int> m_rated_ru;
    QVector<int> m_rated_eng;
    //QVector<RateElement> m_rateLater;
    QVector<QString> m_rateLater;
    QSettings* m_settings;
    CurlProxy* m_proxy;

};

#endif // STORAGE_H
