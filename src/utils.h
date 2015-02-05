#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QList>
#include <QObject>

class QBencodeDict;
class QByteArray;
class Utils
{
public:
    static bool extendBitmap(QByteArray &result, const QByteArray &bitmap);
    static int dictFindInt(const QBencodeDict &dict, const QString &key, int defaultVal);
    static qint64 dictFindLongLong(const QBencodeDict &dict, const QString &key, qint64 defaultVal);
    static QString normalizeSeperator(QString &path);
    static QString normalizeSeperator(const QString &path);
    static void ensurePath(const QString &path);
};

template<typename T>
class AutoList
{
public:
    AutoList(const QList<T*> &list = QList<T*>());
    ~AutoList();

    QList<T*> list;
};

typedef AutoList<QObject> AutoObjectList;

template<typename T>
AutoList<T>::~AutoList()
{
    for (auto obj : list) {
        delete obj;
    }
}

template<typename T>
AutoList<T>::AutoList(const QList<T*> &list)
    : list(list)
{ }

#endif // UTILS_H
