#include <QBencodeValue>
#include <QByteArray>
#include <QString>
#include "utils.h"

bool Utils::extendBitmap(QByteArray &result, const QByteArray &bitmap, int bitsCount)
{
    result.clear();
    result.reserve(bitsCount);
    for (int i = 0; i != bitmap.size(); i++)
        for (int b = 0; b != 8; b++) {
            if (result.size() == bitsCount) { break; }
            if (bitmap.at(i) & (1 << (7 - b))) {
                result.append((char)1);
            } else {
                result.append((char)0);
            }
        }

    return result.size() == bitsCount;
}

int Utils::dictFindInt(const QBencodeDict &dict, const QString &key, int defaultVal)
{
    if (!dict.contains(key)) { return defaultVal; }

    auto val = dict.value(key);

    return (int) val.toInteger(defaultVal);
}

qint64 Utils::dictFindLongLong(const QBencodeDict &dict, const QString &key, qint64 defaultVal)
{
    if (!dict.contains(key)) { return defaultVal; }

    return dict.value(key).toInteger(defaultVal);
}

QString Utils::normalizeSeperator(QString &path)
{
    return path.replace("\\", "/");
}

QString Utils::normalizeSeperator(const QString &path)
{
    QString copy(path);
    return normalizeSeperator(copy);
}

