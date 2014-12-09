#ifndef UTILS_H
#define UTILS_H

#include <QString>

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
};

#endif // UTILS_H
