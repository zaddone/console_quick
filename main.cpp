
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QObject>
#include "view.h"
#include<QDebug>


int main(int argc, char *argv[])
{

    /**
    bool i = true;
    const bool &j = i;

    qDebug() << i<< j;
    i = false;
    qDebug() << i<< j;
    **/

    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/console_quick/main.qml"));


    new View(&viewer,grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials()));

    viewer.showExpanded();
    //viewer.rootContext()->setContextProperty("client", cl);


    return app.exec();

}
