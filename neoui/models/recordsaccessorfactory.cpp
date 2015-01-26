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

RecordsAccessorFactory::RecordsAccessorFactory(QObject *parent)
    : QObject(parent)
{
    initialize();
}

bool RecordsAccessorFactory::initialized = false;
void RecordsAccessorFactory::initialize()
{
    if (initialized) { return; }
    initialized = true;

    knownAccessors.list
            << new AccessorDescription { "uTorrent", "uTorrentConfigPanel.qml" }
            << new AccessorDescription { "qBittorrent", "qBittorrentConfigPanel.qml" };
}

AutoObjectList RecordsAccessorFactory::knownAccessors = AutoObjectList();
QObject *RecordsAccessorFactory::RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                                QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new RecordsAccessorFactory;
}

IRecordsAccessor *RecordsAccessorFactory::createAccessor(const QString &name,
                                                         const QVariantMap &args)
{
    IRecordsAccessor *ira = nullptr;
    if (name == "uTorrent") {
        ira = new uTorrentAccessor;
    } else if (name == "libtorrent") {
        ira = new LibtorrentAccessor;
    } else {
        qDebug() << "warning: unsupported accessor type:" << name;
        return nullptr;
    }
    ira->setup(args);
    return ira;
}

QQmlListProperty<QObject> RecordsAccessorFactory::availableAccessors()
{
    return QQmlListProperty<QObject>(this, &knownAccessors.list,
    [](QQmlListProperty<QObject> *property) {
        auto list = reinterpret_cast<QList<QObject *>*>(property->data);
        return list->length();
    },
    [](QQmlListProperty<QObject> *property, int index) {
        auto list = reinterpret_cast<QList<QObject *>*>(property->data);
        return list->at(index);
    });
}

