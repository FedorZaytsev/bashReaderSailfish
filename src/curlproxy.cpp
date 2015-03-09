#include "curlproxy.h"

CurlProxy::CurlProxy(QObject *parent) :
    QObject(parent)
{
    m_thread = new CurlThread;
    connect(this, &CurlProxy::newTask, m_thread, &CurlThread::newTask, Qt::QueuedConnection);
    m_thread->start();
}

CurlProxy::~CurlProxy() {
    delete m_thread;
}

void CurlProxy::rateRU(QVariant var1, QVariant var2) {
    qDebug()<<"newTask";
    emit newTask(var1.toString(),var2.toString());
}

QQueue<QPair<QString, QString> > CurlProxy::tasks() const {
    return m_thread->tasks();
}

void CurlProxy::terminateThread() {
    m_thread->terminate();
    m_thread->wait();
}


