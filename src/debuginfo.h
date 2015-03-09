#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include <QObject>
#include <QtQuick>
#include <QFile>

class DebugInfo : public QObject
{
    Q_OBJECT
public:
    explicit DebugInfo(QObject *parent = 0);
    Q_INVOKABLE void init();
signals:

public slots:
private:
    QFile* m_log;
    QDebug* m_debug;
};

#endif // DEBUGINFO_H
