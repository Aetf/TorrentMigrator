#include <QFileDialog>
#include "dialoghelper.h"

DialogHelper::DialogHelper(QObject *parent) : QObject(parent)
{ }

QString DialogHelper::getExistingDirectory(const QString &caption,
                                           const QString &dir) const
{
    return QFileDialog::getExistingDirectory(nullptr, caption,
                                             dir.isEmpty() ? QDir::home().path() : dir,
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
}

QObject *DialogHelper::DialogHelperProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new DialogHelper;
}
