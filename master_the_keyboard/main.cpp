#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include "BackEnd.h"

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Fusion");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BackEnd>("local.api.backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/qml/screens/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    BackEnd* backend = engine.rootObjects()[0]->findChildren<BackEnd *>()[0];

    backend->setSampleText(20);
    backend->databaseInit("database.db");

    return app.exec();
}
