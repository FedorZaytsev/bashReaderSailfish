#ifndef CURLTHREAD_H
#define CURLTHREAD_H

#include <QRunnable>
#include <QObject>
#include <QDebug>
#include <QQueue>
#include "curlproxy.h"
class CurlProxy;

class CurlThread : public QThread
{
    Q_OBJECT
public:
    explicit CurlThread(QObject *parent = 0);


    QQueue<QPair<QString, QString> > tasks() const;
    void setTasks(const QQueue<QPair<QString, QString> > &tasks);

public slots:
    void newTask(QString,QString);

protected:
    void run();
signals:

private:
    QQueue<QPair<QString,QString>> m_tasks;
};

#endif // CURLTHREAD_H
