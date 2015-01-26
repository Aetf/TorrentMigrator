#ifndef RECORDSACCESSORFACTORY_H
#define RECORDSACCESSORFACTORY_H

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include "recordsaccessorobject.h"

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

class AccessorList
{
public:
    ~AccessorList();
    QList<QObject*> list;
};

class RecordsAccessorFactory : public QObject
{
    Q_OBJECT
public:
    explicit RecordsAccessorFactory(QObject *parent = 0);

    Q_INVOKABLE
    RecordsAccessorObject *createUTorrentAccessor(const QString &appdata,
                                                  const QString &extra);
    Q_INVOKABLE
    RecordsAccessorObject *createLibTorrentAccessor(const QString &configDir,
                                                    const QString &backupDir);

    Q_INVOKABLE
    QList<QObject *> accessors();

    static QObject *RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                   QJSEngine *scriptEngine);

private:
    static AccessorList knownAccesors;
    static bool initialized;
};



#endif // RECORDSACCESSORFACTORY_H
