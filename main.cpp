#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QIcon>

#include "radixconverter.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    RadixConverter converter;
    engine.rootContext()->setContextProperty("_converter", &converter);

    return app.exec();
}
