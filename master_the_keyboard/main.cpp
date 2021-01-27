#include <QGuiApplication>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <backend.h>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Fusion");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BackEnd>("local.api.backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    BackEnd* backend = engine.rootObjects()[0]->findChildren<BackEnd *>()[0];

    backend->setSampleText(20);
    backend->setupDb("../master_the_keyboard/dataMtk.db");

    return app.exec();
}
