#ifndef RECORDTRANSFORMERFACTORY_H
#define RECORDTRANSFORMERFACTORY_H

#include <QObject>
#include <QQmlListProperty>
#include "irecordstransformer.h"
#include "utils.h"

class QQmlEngine;
class QJSEngine;

class TransformerDescription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    TransformerDescription(IRecordsTransformer* seed, QObject *parent = nullptr);
    ~TransformerDescription();

    QString name() const;
    void setName(const QString &name);

    IRecordsTransformer *seed() const;

signals:
    void nameChanged();

private:
    IRecordsTransformer* m_seed;
    QString m_name;
};

class RecordsTransformerFactory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> availableTransformers
               READ availableTransformers CONSTANT)
public:
    explicit RecordsTransformerFactory(QObject *parent = 0);

    IRecordsTransformer *createTransformer(const QString &name, const QVariantMap &args);
    IRecordsTransformer *createTransformer(const QString &name, const QString &args);

    QQmlListProperty<QObject> availableTransformers();

    static QObject *RecordsTransformerFactoryProvider(QQmlEngine *engine,
                                                      QJSEngine *scriptEngine);
    static void initialize();
private:
    static bool initialized;
    static AutoObjectList knownTransformers;
};

#endif // RECORDTRANSFORMERFACTORY_H
