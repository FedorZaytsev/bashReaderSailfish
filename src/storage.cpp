#include "storage.h"



Storage::Storage(QObject *parent) :
    QObject(parent)
{
    m_fpath = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)).filePath(QCoreApplication::applicationName());

    QDir dir(m_fpath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, m_fpath);

    m_settings = new QSettings;
    m_lang = m_settings->value("lang", "eng").toString();
    setProxy(new CurlProxy(this));
}

Storage::~Storage() {
    delete m_settings;
}

void Storage::loadStorage() {

    QByteArray temp = m_settings->value("rated_ru",QByteArray()).toByteArray();
    QDataStream stream_ru(temp);
    stream_ru >> m_rated_ru;

    temp = m_settings->value("rated_eng",QByteArray()).toByteArray();
    QDataStream stream_eng(temp);
    stream_eng >> m_rated_eng;

    temp = m_settings->value("unrated",QByteArray()).toByteArray();
    QDataStream unrated(temp);
    QQueue<QPair<QString,QString>> queue;
    unrated >> queue;
    int size = queue.size();
    for (int i=0;i<size;i++) {
        QPair<QString,QString> pair = queue.dequeue();
        proxy()->rateRU(QVariant(pair.first),QVariant(pair.second));
    }
}

void Storage::changleLang() {
    if (m_lang=="ru") {
        m_lang = "eng";
    } else {
        m_lang = "ru";
    }
}


void Storage::saveAll() {
    QByteArray m_rated_ru_byte;
    QDataStream stream_ru(&m_rated_ru_byte, QIODevice::WriteOnly);
    stream_ru << m_rated_ru;
    QByteArray m_rated_eng_byte;
    QDataStream stream_eng(&m_rated_eng_byte, QIODevice::WriteOnly);
    stream_eng << m_rated_eng;

    m_settings->setValue("lang", m_lang);
    m_settings->setValue("rated_ru",m_rated_ru_byte);
    m_settings->setValue("rated_eng",m_rated_eng_byte);

    proxy()->terminateThread();
    QByteArray tasks;
    QDataStream d_tasks(&tasks, QIODevice::WriteOnly);
    d_tasks << proxy()->tasks();

    m_settings->setValue("unrated",tasks);

    m_settings->sync();
}

bool Storage::isRatedRU(unsigned int id) {
    return m_rated_ru.indexOf(id) != -1;
}

void Storage::addRatedRU(unsigned int id) {
    if (!isRatedRU(id)) {
        m_rated_ru.push_back(id);
    }
}
bool Storage::isRatedENG(unsigned int id) {
    return m_rated_eng.indexOf(id) != -1;
}

void Storage::addRatedENG(unsigned int id) {
    if (!isRatedENG(id)) {
        m_rated_eng.push_back(id);
    }
}

void Storage::rateLaterRU(QVariant ident, QVariant action, QVariant idx) {
    //m_rateLater.push_back(RateElement(ident.toString(),action.toString(),idx.toInt()));
}

void Storage::rateLaterENG(QVariant url) {
    m_rateLater.push_back(url.toString());
}


QString Storage::rateUrl(int id) {
    Q_ASSERT(id<m_rateLater.count() && id>=0);
    return m_rateLater[id];
}

void Storage::deleteRateElement(int id) {
    Q_ASSERT(id<m_rateLater.count() && id>=0);
    m_rateLater.remove(id);
}

void Storage::rateRU(QVariant url, QVariant act) {
    proxy()->rateRU(url,act);
}

CurlProxy *Storage::proxy() const
{
    return m_proxy;
}

void Storage::setProxy(CurlProxy *proxy)
{
    m_proxy = proxy;
}


