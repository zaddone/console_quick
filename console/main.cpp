#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "show.h"
#include <QQuickItem>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //engine.rootContext()
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //QList<QObject *> qmlList = engine.rootObjects();
    if (engine.rootObjects().isEmpty())
        return -1;
    grpc::ChannelArguments arg;
    arg.SetInt("GRPC_ARG_KEEPALIVE_PERMIT_WITHOUT_CALLS",1);
    arg.SetInt("GRPC_ARG_KEEPALIVE_TIME_MS",30*1000);
    arg.SetInt("GRPC_ARG_KEEPALIVE_TIMEOUT_MS",5*1000);

    arg.SetInt("GRPC_ARG_MAX_CONNECTION_IDLE_MS",5*1000);
    //arg.SetInt("GRPC_ARG_SERVER_HANDSHAKE_TIMEOUT_MS",5);
    //arg.SetInt("GRPC_ARG_HTTP2_BDP_PROBE",0);

    //GRPC_ARG_MAX_CONNECTION_IDLE_MS



    Show s(&engine,grpc::CreateCustomChannel("192.168.1.60:50051",grpc::InsecureChannelCredentials(),arg));
    return app.exec();

}
