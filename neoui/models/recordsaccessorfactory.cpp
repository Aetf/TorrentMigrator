#include "recordsaccessorfactory.h"
#include "utorrentaccessor.h"
#include "libtorrentaccessor.h"

AccessorDescription::AccessorDescription(QObject *parent)
    : QObject(parent)
{ }

AccessorDescription::AccessorDescription(const QString &name, const QString &source,
                                         QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_configPanelSource(source)
{ }

QString AccessorDescription::name() const
{
    return m_name;
}

void AccessorDescription::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QString AccessorDescription::configPanelSource() const
{
    return m_configPanelSource;
}

void AccessorDescription::setConfigPanelSource(const QString &source)
{
    if (m_configPanelSource != source) {
        m_configPanelSource = source;
        emit configPanelSourceChanged();
    }
}

AccessorList::~AccessorList()
{
    for (auto obj : list) {
        delete obj;
    }
}

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
    auto ira = new LibtorrentAccessor;
    QVariantHash args;
    args["configDir"] = configDir;
    args["backupDir"] = backupDir;
    ira->setup(args);
    return new RecordsAccessorObject(ira);
}

QList<QObject *> RecordsAccessorFactory::accessors()
{
    return knownAccesors.list;
}

AccessorList RecordsAccessorFactory::knownAccesors = AccessorList();
bool RecordsAccessorFactory::initialized = false;
QObject *RecordsAccessorFactory::RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if (!initialized) {
        knownAccesors.list
                << new AccessorDescription { "uTorrent", "uTorrentConfigPanel.qml" }
                << new AccessorDescription { "qBittorrent", "qBittorrentConfigPanel.qml" };
        initialized = true;
    }
    return new RecordsAccessorFactory;
}
