#ifndef CURLPROXY_H
#define CURLPROXY_H

#include <QObject>
#include <QThreadPool>
#include <QVariant>
#include "curlthread.h"

class CurlThread;

class CurlProxy : public QObject
{
    Q_OBJECT
public:
    explicit CurlProxy(QObject *parent = 0);
    ~CurlProxy();
    void rateRU(QVariant , QVariant );
    QQueue<QPair<QString,QString> > tasks() const;
    void terminateThread();

signals:
    void newTask(QString,QString);
public slots:

private:
    QVector<QPair<QString,QString>> m_nonRated;
    CurlThread* m_thread;
};

#endif // CURLPROXY_H
