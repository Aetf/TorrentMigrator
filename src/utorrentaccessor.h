#ifndef UTORRENTACCESSOR_H
#define UTORRENTACCESSOR_H

#include <QBencodeValue>
#include "irecordsaccessor.h"
#include "simpletorrentinfo.h"

class uTorrentAccessor : public IRecordsAccessor
{
public:
    uTorrentAccessor();
    ~uTorrentAccessor();

    /*!
     * \brief setup
     * \param args
     *     "appdata" => path to appdata dir
     *     "extratorrent" => path to extratorrent dir
     * \return
     */
    virtual bool setup(QVariantMap args);
    virtual bool readAll(QList<TorrentRecord> &list);
    virtual bool writeAll(QList<TorrentRecord> &records);
    virtual bool add(const TorrentRecord &record);
    virtual bool update(const TorrentRecord &record);
    virtual bool remove(const QString &hash);

private:
    bool fillStorageInfo(TorrentRecord &record, const QBencodeDict &uTorrentRecord,
                         const QString &key);
    void fillSavePath(TorrentRecord &record, const QBencodeDict &uTorrentRecord);

    std::pair<SimpleTorrentInfo, QString> loadTorrentFile(const QString &key);
    bool loadResumeData();
    bool writeResumeData();

    QString appdataPath;
    QString extraTorrentPath;
    QBencodeDict resumeData;

    bool ready;

    enum CONSTANTS {
        MAX_CONNECTIONS_NO = -1,

    };
};

#endif // UTORRENTACCESSOR_H
