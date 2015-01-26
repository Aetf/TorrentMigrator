#include "recordstransformerfactory.h"
#include "devicemaptransformer.h"

TransformerDescription::TransformerDescription(QObject *parent)
    : QObject(parent)
{ }

TransformerDescription::TransformerDescription(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
{ }

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
RecordsTransformerFactory::RecordsTransformerFactory(QObject *parent)
    : QObject(parent)
{
    initialize();
}

bool RecordsTransformerFactory::initialized = false;
void RecordsTransformerFactory::initialize()
{
    if (initialized) { return; }
    initialized = true;
}

AutoObjectList RecordsTransformerFactory::knownTransformers = AutoObjectList();
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
