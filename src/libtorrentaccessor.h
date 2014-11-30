#ifndef LIBTORRENTACCESSOR_H
#define LIBTORRENTACCESSOR_H

#include <QString>
#include "irecordsaccessor.h"
#include "torrentrecord.h"
#include "simpletorrentinfo.h"


class LibtorrentAccessor : public IRecordsAccessor
{
public:
    LibtorrentAccessor();
    ~LibtorrentAccessor();

    virtual bool setup(QVariantHash args);
    virtual bool readAll(QList<TorrentRecord> &list);
    virtual bool writeAll(QList<TorrentRecord> &records);
    virtual bool add(const TorrentRecord &record);
    virtual bool update(const TorrentRecord &record);
    virtual bool remove(const QString &hash);

private:
    QString configDir;
    QString backupDir;

    bool ready;

    enum RatioLimit {
        USE_GLOBAL_RATIO = -2,
        NO_RATIO_LIMIT = -1
    };

    enum CONSTANTS {
        MAX_CONNECTION_NO = (1 << 24) - 1,
    };

    QStringList recordHashs();
    void deleteConfRecord(const QString &hash);

    bool fillStorageInfo(TorrentRecord &record, const QString &hash, const SimpleTorrentInfo &ti);
    void fillFileInfos(TorrentRecord &record, const QString &hash);
    void fillLastActive(TorrentRecord &record, const QString &hash);
    void fillMaxConnections(TorrentRecord &record, const QString &hash);
    void fillRatioLimit(TorrentRecord &record, const QString &hash);
    void fillTrackers(TorrentRecord &record, const QString &hash);
    void fillLabels(TorrentRecord &record, const QString &hash);

    // info in config
    void setConfValue(const QString &hash, const QString &key, const QVariant &value);
    QVariant getConfValue(const QString &hash, const QString &key,
                          const QVariant &defaultVal = QVariant()) const;
    // info in fastresume
    bool hasResumeData(const QString &hash) const;
    QVariant getResumeValue(const QString &hash, const QString &key,
                            const QVariant &defaultVal = QVariant()) const;
    // info in torrent file
    std::pair<SimpleTorrentInfo, QString> locateTorrentFile(const QString &hash);

    // convinent getters and setters
    void setRatioLimit(const QString &hash, double ratio);
    double getRatioLimit(const QString &hash);
    void setAddedDate(const QString &hash, const QDateTime &time);
    QDateTime getAddedDate(const QString &hash);
    void setSeedDate(const QString &hash, const QDateTime &time);
    QDateTime getSeedDate(const QString &hash);

    void setSavePath(const QString &hash, const QString &save_path);
    void setLabel(const QString &hash, const QString &label);
    void setName(const QString &hash, const QString &name);
    void setPriority(const QString &hash, const int &queue_pos);
    void setSeedStatus(const QString &hash, const bool seedStatus);

    QString getSavePath(const QString &hash);
    QString getLabel(const QString &hash);
    QString getName(const QString &hash);
    int getPriority(const QString &hash);
    bool isSeed(const QString &hash);

    int getBlocksPerPiece(const QString &hash);
};

#endif // LIBTORRENTACCESSOR_H
