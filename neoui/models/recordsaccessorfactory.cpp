#include "recordsaccessorfactory.h"
#include "utorrentaccessor.h"
#include "libtorrentaccessor.h"

RecordsAccessorFactory::RecordsAccessorFactory(QObject *parent) : QObject(parent)
{ }

RecordsAccessorObject *RecordsAccessorFactory::createUTorrentAccessor(
    const QString &appdata, const QString &extra)
{
    auto ira = new uTorrentAccessor;
    QVariantHash args;
    args["appdata"] = appdata;
    args["extratorrent"] = extra;
    ira->setup(args);
    return new RecordsAccessorObject(ira);
}

RecordsAccessorObject *RecordsAccessorFactory::createLibTorrentAccessor(
    const QString &configDir, const QString &backupDir)
{
    auto ira = new uTorrentAccessor;
    QVariantHash args;
    args["configDir"] = configDir;
    args["backupDir"] = backupDir;
    ira->setup(args);
    return new RecordsAccessorObject(ira);
}

QObject *RecordsAccessorFactory::RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new RecordsAccessorFactory;
}
