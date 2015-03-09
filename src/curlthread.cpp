#include "curlthread.h"


CurlThread::CurlThread(QObject *parent) : QThread(parent)
{
}

void CurlThread::run() {
    qDebug()<<"Thread started";

    while (true) {
        if (m_tasks.size()) {
            qDebug()<<"emit";
            QPair<QString,QString> p = m_tasks.head();
            QString cmd = QString("curl --request POST 'http://bash.im/quote/%1/%2' --data \"quote=%1&act=%2\" -H \"Origin: http://bash.im\" -H \"Referer: http://bash.im/index/1\"").arg(p.first,p.second);
            if (system(NULL)) {
                int result = system(cmd.toStdString().c_str());
                if (!result) {
                    m_tasks.dequeue();
                }else{
                    qDebug()<<"error";
                }
            }
        }
        msleep(60000);
    }
}
QQueue<QPair<QString, QString> > CurlThread::tasks() const {
    return m_tasks;
}

void CurlThread::setTasks(const QQueue<QPair<QString, QString> > &tasks) {
    m_tasks = tasks;
}

void CurlThread::newTask(QString ident,QString act) {
    qDebug()<<"CurlThread::newTask";
    m_tasks.enqueue(QPair<QString,QString>(ident,act));
}

