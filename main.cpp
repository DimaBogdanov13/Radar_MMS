#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "main_page_logic.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<Main_Page_Logic>("Main_Page_Logic", 1, 0, "Main_Page_Logic");

    qmlRegisterUncreatableType<Actions>("Actions", 1, 0, "Actions", "");


    QQmlApplicationEngine engine;

    engine.load(QUrl("qrc:/main.qml"));



    return app.exec();
}
