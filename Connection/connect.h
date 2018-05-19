#ifndef CONNECT_H
#define CONNECT_H


#include <grpcpp/grpcpp.h>
#include "console.grpc.pb.h"
//#include "greeter.h"

using grpc::Channel;
using console::Greeter;
#include <QObject>
#include <QVariant>
class Connect : public QObject
{
    Q_OBJECT
public:
    explicit Connect(const std::string & addr = "192.168.1.60:50051");
    ~Connect();
    //void load(GreeterClient * r);
    //void unload();
    //GreeterClient * greeter();
    std::unique_ptr<Greeter::Stub> stub_;
private:

signals:
    void resultReady(const QVariant &);
    //GreeterClient * rpcClass;
};

#endif // CONNECT_H
