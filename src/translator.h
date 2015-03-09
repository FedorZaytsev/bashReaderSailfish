#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QCoreApplication>
#include <QtQuick>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = 0);
    Q_INVOKABLE void translate(QString lang);

signals:

public slots:
private:
    QTranslator* translator;

};

#endif // TRANSLATOR_H
