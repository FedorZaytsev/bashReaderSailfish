#include "htmlparse.h"

#define QUOTE_START "<div class=\"quote\">"
#define RATING_START "class=\"rating\">"
#define RATING_END "</span>"
#define TIME_START "<span class=\"date\">"
#define TIME_END "</span>"
#define ID_START "class=\"id\">"
#define ID_END "</a>"
#define TEXT_START "<div class=\"text\">"
#define TEXT_END "</div>"
#define ID2_START "<span class=\"abysstop\">"
#define ID2_END "</span>"
#define TIME2_START "<span class=\"abysstop-date\">"
#define TIME2_END "</span>"
#define ID3_START "class=\"id\">"
#define ID3_END "</span>"
#define NEXT_PAGE_START "<link rel=\"next\" href=\""
#define NEXT_PAGE_END "\" />"
#define NEXT_PAGE2_START "<div class=\"quote more\"><a href=\""
#define NEXT_PAGE2_END "\" class=\"button\">"
#define NEXT_PAGE3_START "<a href=\""
#define NEXT_PAGE3_END "\">"
#define NOT_FOUND -1

#define ENG_QUOTE_START "<p class=\"quote\">"
#define ENG_ID_START "<b>#"
#define ENG_ID_END "</b>"
#define ENG_RATING_START "class=\"qa\">+</a>("
#define ENG_RATING_END ")"
#define ENG_TEXT_START "<p class=\"qt\">"
#define ENG_TEXT_END "</p>"
#define ENG_NEXT_PAGE_START "<font class=\"qa\">"
#define END_NEXT_PAGE2_START "</font>-<a href=\"."
#define ENG_NEXT_PAGE_END "\" class=\"qa\">"
#define ENG_RATE_KEY_START "<a href=\"./?le="
#define ENG_RATE_KEY_END "&"


#define IS_BASH_IM "<title>Цитатник Рунета</title>"


HTMLParse::HTMLParse(QObject *parent) :
    QObject(parent)
{
    proc = new QProcess;
}

HTMLParse::~HTMLParse() {
    delete proc;
}

void HTMLParse::replyFinished(QNetworkReply* reply) {
    qDebug()<<"ANSWER: "<<reply->readAll();
}

void HTMLParse::parseEng(QString str)
{
    m_data.clear();
    m_nextPage = "";
    uint64_t split_pos = 0;
    uint64_t start_pos = 0;

    while (str.indexOf(ENG_QUOTE_START,split_pos) != NOT_FOUND) {
        bashQuote b;

        if ((start_pos = str.indexOf(ENG_ID_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ENG_ID_START).length();
            b.id = str.mid(split_pos, str.indexOf(ENG_ID_END,split_pos) - split_pos);
        }

        if ((start_pos = str.indexOf(ENG_RATE_KEY_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ENG_RATE_KEY_START).length();
            b.rate_key = str.mid(split_pos, str.indexOf(ENG_RATE_KEY_END,split_pos) - split_pos);
        }

        if ((start_pos = str.indexOf(ENG_RATING_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ENG_RATING_START).length();
            QString rating = str.mid(split_pos, str.indexOf(ENG_RATING_END,split_pos) - split_pos);
            uint64_t __idx = rating.indexOf(">")+1;
            b.rating = rating.mid( __idx, rating.indexOf("</") -__idx );
        }

        if ((start_pos = str.indexOf(ENG_TEXT_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ENG_TEXT_START).length();
            QTextDocument text;
            text.setHtml(str.mid(split_pos, str.indexOf(ENG_TEXT_END,split_pos) - split_pos));
            b.text = text.toPlainText();
        }

        m_data.push_back(b);
    }

    if ((start_pos = str.indexOf(ENG_NEXT_PAGE_START,split_pos)) != NOT_FOUND) {
        split_pos = start_pos + QString(ENG_NEXT_PAGE_START).length();
        if ((start_pos = str.indexOf(END_NEXT_PAGE2_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(END_NEXT_PAGE2_START).length();
            m_nextPage = "http://bash.org" + str.mid(split_pos, str.indexOf(ENG_NEXT_PAGE_END,split_pos) - split_pos);
        }
    }
}

void HTMLParse::parseRu(QString str)
{
    m_data.clear();
    m_nextPage = "";
    uint64_t split_pos = 0;
    uint64_t start_pos = 0;
    while (str.indexOf(QUOTE_START,split_pos) != NOT_FOUND) {
        bashQuote b;

        if ((start_pos = str.indexOf(RATING_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(RATING_START).length();
            b.rating = str.mid(split_pos, str.indexOf(RATING_END,split_pos) - split_pos);
        }

        if ((start_pos = str.indexOf(TIME_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(TIME_START).length();
            b.date = str.mid(split_pos, str.indexOf(TIME_END,split_pos) - split_pos);
        } else if ((start_pos = str.indexOf(TIME2_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(TIME2_START).length();
            b.date = str.mid(split_pos, str.indexOf(TIME2_END,split_pos) - split_pos);
        }

        if ((start_pos = str.indexOf(ID_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ID_START).length();
            b.id = str.mid(split_pos+1, str.indexOf(ID_END,split_pos) - split_pos - 1);
        } else if ((start_pos = str.indexOf(ID2_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ID2_START).length();
            b.id = str.mid(split_pos+1, str.indexOf(ID2_END,split_pos) - split_pos - 1);
        } else if ((start_pos = str.indexOf(ID3_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(ID3_START).length();
            b.id = str.mid(split_pos+1, str.indexOf(ID3_END,split_pos) - split_pos - 1);
        }

        if ((start_pos = str.indexOf(TEXT_START,split_pos)) != NOT_FOUND) {
            split_pos = start_pos + QString(TEXT_START).length();
            QTextDocument text;
            text.setHtml(str.mid(split_pos, str.indexOf(TEXT_END,split_pos) - split_pos));
            b.text = text.toPlainText();
        }

        m_data.push_back(b);
    }


    if (m_nextPage =="" && (start_pos = str.indexOf(NEXT_PAGE_START,split_pos)) != NOT_FOUND) {
        split_pos = start_pos + QString(NEXT_PAGE_START).length();
        m_nextPage = "http://bash.im" + str.mid(split_pos, str.indexOf(NEXT_PAGE_END,split_pos) - split_pos);
    }
    if (m_nextPage =="" && (start_pos = str.indexOf(NEXT_PAGE2_START,split_pos)) != NOT_FOUND) {
        split_pos = start_pos + QString(NEXT_PAGE2_START).length();
        m_nextPage = "http://bash.im" + str.mid(split_pos, str.indexOf(NEXT_PAGE2_END,split_pos) - split_pos);
    }
    if (m_nextPage =="" && (start_pos = str.indexOf(NEXT_PAGE3_START,split_pos)) != NOT_FOUND) {
        split_pos = start_pos + QString(NEXT_PAGE3_START).length();
        m_nextPage = "http://bash.im" + str.mid(split_pos, str.indexOf(NEXT_PAGE3_END,split_pos) - split_pos);
    }
}


int HTMLParse::count() {
    return m_data.count();
}

QString HTMLParse::text(int id) {
    Q_ASSERT(id<m_data.count() && id>=0);
    return m_data[id].text;
}

QString HTMLParse::id(int id) {
    Q_ASSERT(id<m_data.count() && id>=0);
    return m_data[id].id;
}

QString HTMLParse::rating(int id) {
    Q_ASSERT(id<m_data.count() && id>=0);
    return m_data[id].rating;
}

QString HTMLParse::date(int id) {
    Q_ASSERT(id<m_data.count() && id>=0);
    return m_data[id].date;
}

QString HTMLParse::rate_key(int id) {
    Q_ASSERT(id<m_data.count() && id>=0);
    return m_data[id].rate_key;
}

QString HTMLParse::wantMore() {
    return m_nextPage;
}
