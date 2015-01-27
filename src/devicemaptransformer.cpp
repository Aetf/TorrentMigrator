#include <QRegExp>
#include "devicemaptransformer.h"
#include "utils.h"

DeviceMapTransformer::DeviceMapTransformer()
{

}

DeviceMapTransformer::~DeviceMapTransformer()
{

}

QString DeviceMapTransformer::name() const
{
    return QStringLiteral("DeviceMapTransformer");
}

IRecordsTransformer *DeviceMapTransformer::allocate() const
{
    return new DeviceMapTransformer();
}

/*!
 * \brief setup
 * \param args
 *     "I: => /media/xxx"
 *     "D: => /mnt/abc"
 * \return
 */
bool DeviceMapTransformer::setup(QString args)
{
    const QString mark("=>");
    QVariantMap argsMap;
    for (auto line : args.split('\n')) {
        int idx = line.indexOf(mark);
        if (idx != -1) {
            auto left = line.left(idx);
            auto right = line.right(line.size() - mark.size() - idx);
            if (!right.trimmed().isEmpty()) {
                argsMap[left.trimmed()] = right.trimmed();
            }
        }
    }
    return setup(argsMap);
}

/*!
 * \brief setup
 * \param args
 *     "I:/" : "/media/xxx"
 *     "D:" : "/mnt/abc"
 * \return
 */
bool DeviceMapTransformer::setup(QVariantMap args)
{
    for (auto key : args.keys()) {
        if (!QRegExp(R"([a-zA-Z]:[/\\]?)").exactMatch(key)) { continue; }
        if (!args[key].canConvert<QString>()) { continue; }

        auto lowerKey = Utils::normalizeSeperator(key.toLower());
        if (!lowerKey.endsWith('/')) lowerKey += '/';
        auto normalizedPath = Utils::normalizeSeperator(args[key].toString());
        if (!normalizedPath.endsWith('/')) normalizedPath += '/';

        devicesMap[lowerKey] = normalizedPath;
        reverseDevicesMap[normalizedPath] = lowerKey;

        qDebug() << "devicesMap added:"
                 << lowerKey << "=>" << normalizedPath;
    }
    return true;
}

TorrentRecord DeviceMapTransformer::transform(const TorrentRecord &input) const
{
    auto result = input;
    for (auto key : devicesMap.keys()) {
        if (result.save_path.startsWith(key, Qt::CaseInsensitive)) {
            result.save_path.replace(key, devicesMap[key], Qt::CaseInsensitive);
            break;
        }
    }
    return result;
}

TorrentRecord DeviceMapTransformer::transformBack(const TorrentRecord &input) const
{
    auto result = input;
    for (auto key : reverseDevicesMap.keys()) {
        if (result.save_path.startsWith(key, Qt::CaseInsensitive)) {
            result.save_path.replace(key, reverseDevicesMap[key]);
            break;
        }
    }
    return result;
}
