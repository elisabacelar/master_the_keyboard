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

    return app.exec();
}
