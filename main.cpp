#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "view.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.rootContext()
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //new View(&engine,grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials()));
    new View(&engine,grpc::CreateChannel("192.168.1.60:50051",grpc::InsecureChannelCredentials()));
    return app.exec();
}
