#include "recordsaccessorfactory.h"
#include "utorrentaccessor.h"
#include "libtorrentaccessor.h"

AccessorDescription::AccessorDescription(IRecordsAccessor *seed, const QString &source,
                                         QObject *parent)
    : QObject(parent)
    , m_seed(seed)
    , m_name(seed->name())
    , m_configPanelSource(source)
{ }

AccessorDescription::~AccessorDescription()
{
    delete m_seed;
}

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

IRecordsAccessor *AccessorDescription::seed() const
{
    return m_seed;
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
    << new AccessorDescription { new uTorrentAccessor(), "uTorrentConfigPanel.qml" }
    << new AccessorDescription { new LibtorrentAccessor(), "qBittorrentConfigPanel.qml" };
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
    for (auto obj : knownAccessors.list) {
        auto desc = reinterpret_cast<AccessorDescription *>(obj);
        if (desc->name() == name) {
            ira = desc->seed()->allocate();
            break;
        }
    }

    if (ira) {
        ira->setup(args);
    } else {
        qDebug() << "warning: unsupported accessor type:" << name;
    }
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

