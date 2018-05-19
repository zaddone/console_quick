#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "show.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.rootContext()
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QList<QObject *> qmlList = engine.rootObjects();
    if (qmlList.isEmpty())
        return -1;
    //new View(&engine,grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials()));

    Show *s = new Show(qmlList[0], "192.168.1.60:50051");

    engine.rootContext()->setContextProperty("view", s);
    //s->Start();
    return app.exec();
}
