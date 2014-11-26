#include <QBencodeDocument>
#include <QBencodeValue>
#include <QByteArray>
#include <QFile>
#include "utorrentaccessor.h"

uTorrentAccessor::uTorrentAccessor()
    : ready(false)
{

}

uTorrentAccessor::~uTorrentAccessor()
{

}

bool uTorrentAccessor::setup(QVariantHash args)
{
    appdataPath = args["appdata"].toString();

    QFile resumeFile(appdataPath + "/resume.dat");
    if (!resumeFile.open(QIODevice::ReadOnly)) return false;

    auto doc = QBencodeDocument::fromBencode(resumeFile.readAll());
    if (doc.isNull()) return false;

    // quick sanity check, valid resume data should have a dict as root
    if (doc.value().type() != QBencodeValue::Dict) return false;

    // remove .fileguard so uTorrent will accept the file
    resumeData = doc.value().toDict();
    resumeData.remove(QString::fromUtf8(".fileguard"));

    ready = true;
}

bool uTorrentAccessor::add(const TorrentRecord &/*record*/)
{
    if (!ready) return false;

    // FUTURE: uTorrentAccessor::add
    return false;
}

bool uTorrentAccessor::remove(const QString &hash)
{
    if (!ready) return false;

    for (auto key : resumeData.keys()) {
        if (resumeData[key].type() != QBencodeValue::Dict) continue;
        auto dict = resumeData[key].toDict();

        auto hashbytes = QByteArray::fromHex(hash.toLatin1());
        if (dict["info"].toByteArray() == hashbytes) {
            resumeData.remove(key);
            return true;
        }
    }
    return false;
}

bool uTorrentAccessor::update(const TorrentRecord &/*record*/)
{
    if (!ready) return false;
    // FUTURE: uTorrentAccessor::update
/*
    for (auto key : resumeData.keys()) {
        if (resumeData[key].type() != QBencodeValue::Dict) continue;
        auto dict = resumeData[key].toDict();

        auto hashbytes = QByteArray::fromHex(record.info_hash.toLatin1());
        if (dict["info"].toByteArray() == hashbytes) {

            return true;
        }
    }
*/
    return false;
}

QList<TorrentRecord> uTorrentAccessor::readAll()
{

}

bool uTorrentAccessor::writeAll(QList<TorrentRecord> &/*records*/)
{
    if (!ready) return false;
    // FUTURE: uTorrentAccessor::writeAll
    return false;
}

