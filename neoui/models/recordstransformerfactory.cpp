#include "recordstransformerfactory.h"
#include "devicemaptransformer.h"
#include "pathregextransformer.h"

TransformerDescription::TransformerDescription(IRecordsTransformer *seed, QObject *parent)
    : QObject(parent)
    , m_seed(seed)
    , m_name(seed->name())
{ }

TransformerDescription::~TransformerDescription()
{
    delete m_seed;
}

QString TransformerDescription::name() const
{
    return m_name;
}

void TransformerDescription::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

IRecordsTransformer *TransformerDescription::seed() const
{
    return m_seed;
}

RecordsTransformerFactory::RecordsTransformerFactory(QObject *parent)
    : QObject(parent)
{
    initialize();
}

bool RecordsTransformerFactory::initialized = false;
AutoObjectList RecordsTransformerFactory::knownTransformers = AutoObjectList();
void RecordsTransformerFactory::initialize()
{
    if (initialized) { return; }
    initialized = true;

    knownTransformers.list
    << new TransformerDescription { new DeviceMapTransformer() }
    << new TransformerDescription { new PathRegexTransformer() };
}

QObject *RecordsTransformerFactory::RecordsTransformerFactoryProvider(QQmlEngine *engine,
                                                                      QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new RecordsTransformerFactory;
}

QQmlListProperty<QObject> RecordsTransformerFactory::availableTransformers()
{
    return QQmlListProperty<QObject>(this, &knownTransformers.list,
    [](QQmlListProperty<QObject> *property) {
        auto list = reinterpret_cast<QList<QObject *>*>(property->data);
        return list->length();
    },
    [](QQmlListProperty<QObject> *property, int index) {
        auto list = reinterpret_cast<QList<QObject *>*>(property->data);
        return list->at(index);
    });
}

IRecordsTransformer *RecordsTransformerFactory::createTransformer(const QString &name,
                                                                  const QVariantMap &args)
{
    IRecordsTransformer *irt = nullptr;
    for (auto obj : knownTransformers.list) {
        auto desc = reinterpret_cast<TransformerDescription*>(obj);
        if (desc->name() == name) {
            irt = desc->seed()->allocate();
            break;
        }
    }
    if (irt) {
        irt->setup(args);
    } else {
        qDebug() << "warning: unsupported transformer type:" << name;
    }
    return irt;
}

IRecordsTransformer *RecordsTransformerFactory::createTransformer(const QString &name,
                                                                  const QString &args)
{
    IRecordsTransformer *irt = nullptr;
    for (auto obj : knownTransformers.list) {
        auto desc = reinterpret_cast<TransformerDescription*>(obj);
        if (desc->name() == name) {
            irt = desc->seed()->allocate();
            break;
        }
    }
    if (irt) {
        irt->setup(args);
    } else {
        qDebug() << "warning: unsupported transformer type:" << name;
    }
    return irt;
}
