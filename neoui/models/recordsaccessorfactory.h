#ifndef RECORDSACCESSORFACTORY_H
#define RECORDSACCESSORFACTORY_H

#include <QObject>
#include <QQmlListProperty>
#include <QString>
#include "irecordsaccessor.h"
#include "utils.h"

class QQmlEngine;
class QJSEngine;

class AccessorDescription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString configPanelSource
               READ configPanelSource
               WRITE setConfigPanelSource
               NOTIFY configPanelSourceChanged)
public:
    AccessorDescription(QObject *parent = nullptr);
    AccessorDescription(const QString &name, const QString &source, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString configPanelSource() const;
    void setConfigPanelSource(const QString &source);
signals:
    void nameChanged();
    void configPanelSourceChanged();
private:
    QString m_name;
    QString m_configPanelSource;
};

class RecordsAccessorFactory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> availableAccessors READ availableAccessors)
public:
    explicit RecordsAccessorFactory(QObject *parent = 0);

    IRecordsAccessor *createAccessor(const QString &name, const QVariantMap &args);

    QQmlListProperty<QObject> availableAccessors();

    static QObject *RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                   QJSEngine *scriptEngine);

    static void initialize();

private:
    static AutoObjectList knownAccessors;
    static bool initialized;
};



#endif // RECORDSACCESSORFACTORY_H
