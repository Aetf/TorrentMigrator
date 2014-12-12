#ifndef RECORDSACCESSORFACTORY_H
#define RECORDSACCESSORFACTORY_H

#include <QObject>
#include <QString>
#include "recordsaccessorobject.h"

class QQmlEngine;
class QJSEngine;

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

    static QObject *RecordsAccessorFactoryProvider(QQmlEngine *engine,
                                                   QJSEngine *scriptEngine);
};



#endif // RECORDSACCESSORFACTORY_H
