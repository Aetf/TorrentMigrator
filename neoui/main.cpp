#include <QApplication>
#include <QDesktopWidget>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
