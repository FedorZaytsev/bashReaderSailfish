#include "translator.h"

Translator::Translator(QObject *parent) :
    QObject(parent)
{
}

void Translator::translate(QString lang) {
    return;
    if (!translator) {
        translator = new QTranslator();
        QCoreApplication::installTranslator(translator);
    }

    qDebug()<<"translate:"<<(QLatin1String("bashReaderOnlyQML-")+lang+QLatin1String(".ts"));
    translator->load(QLatin1String("bashReaderOnlyQML-")+lang+QLatin1String(""), QLatin1String("/i18n"));
}
