#ifndef DEVICEMAPTRANSFORMER_H
#define DEVICEMAPTRANSFORMER_H

#include <QHash>
#include <QString>
#include "irecordstransformer.h"

class DeviceMapTransformer : public IRecordsTransformer
{
public:
    DeviceMapTransformer();
    ~DeviceMapTransformer();

    /*!
     * \brief setup
     * \param args
     *     "I:" => "/media/xxx"
     *     "D:" => "/mnt/abc"
     * \return
     */
    virtual bool setup(QVariantHash args);
    virtual bool setup(QString args);
    virtual TorrentRecord transform(const TorrentRecord &input) const;
    virtual TorrentRecord transformBack(const TorrentRecord &input) const;

private:
    QHash<QString, QString> devicesMap;
    QHash<QString, QString> reverseDevicesMap;
};

#endif // DEVICEMAPTRANSFORMER_H
