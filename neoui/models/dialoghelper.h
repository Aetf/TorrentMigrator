#ifndef DIALOGHELPER_H
#define DIALOGHELPER_H

#include <QObject>
#include <QString>

class QQmlEngine;
class QJSEngine;

class DialogHelper : public QObject
{
    Q_OBJECT
public:
    explicit DialogHelper(QObject *parent = 0);

    Q_INVOKABLE
    QString getExistingDirectory(const QString &caption = QString(),
                                 const QString &dir = QString()) const;


    static QObject *DialogHelperProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
};

#endif // DIALOGHELPER_H
