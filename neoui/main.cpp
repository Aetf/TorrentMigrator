#include <QApplication>
#include <QDesktopWidget>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QStyle>
#include <QtQml>
#include "models/recordsmodel.h"
#include "models/recordsaccessorobject.h"
#include "models/recordsaccessorfactory.h"

void registerRecordsModel();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerRecordsModel();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // get ApplicationWindow object and center it
    Q_ASSERT(!engine.rootObjects().isEmpty());
    auto * const window = qobject_cast<QQuickWindow*>(engine.rootObjects().front());
    Q_ASSERT(window);
    window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window->size(),
                                            qApp->desktop()->availableGeometry()));
    return app.exec();
}

void registerRecordsModel()
{
    qmlRegisterSingletonType<RecordsAccessorFactory>("RecordsModel", 1, 0, "RecordsAccessorFactory", RecordsAccessorFactory::RecordsAccessorFactoryProvider);
    qmlRegisterType<RecordsModel>("RecordsModel", 1, 0, "RecordsModel");
    qmlRegisterType<RecordsAccessorObject>("RecordsModel", 1, 0, "RecordsAccessorObject");
}
