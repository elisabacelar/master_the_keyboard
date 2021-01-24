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

    //Backend

    //engine.rootContext()->setContextProperty("inputText", QDateTime::currentDateTime());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    BackEnd* backend = engine.rootObjects()[0]->findChildren<BackEnd *>()[0];

    backend->setReferenceText("Long text to be written by the user of this application (master the keyboard).");

    return app.exec();
}
