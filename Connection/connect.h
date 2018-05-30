#ifndef CONNECT_H
#define CONNECT_H

//#include <QtQml/qqmlengine.h>
#include <QQmlApplicationEngine>
#include <grpcpp/grpcpp.h>
#include "console.grpc.pb.h"
//#include "greeter.h"
//#include <QQuickItem>
//using grpc::Channel;
using console::Greeter;
#include <QObject>
#include <QVariant>
class Connect : public QObject
{
    Q_OBJECT
public:
    explicit Connect(QQmlApplicationEngine * Engine,const  std::shared_ptr<::grpc::ChannelInterface> &_channel);
    ~Connect();
    //void load(GreeterClient * r);
    //void unload();
    //GreeterClient * greeter();
    std::unique_ptr<Greeter::Stub> stub_;

    QQmlApplicationEngine * Engine_;

private:

signals:
    void resultReady(const QVariant &);
    //GreeterClient * rpcClass;
};

#endif // CONNECT_H
