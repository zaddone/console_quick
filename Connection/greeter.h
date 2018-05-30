#ifndef GREETER_H
#define GREETER_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <grpcpp/grpcpp.h>
#include "console.grpc.pb.h"
#include "connect.h"

using grpc::Channel;
using console::Greeter;


class GreeterClient : public QObject
{
    Q_OBJECT

public:
    explicit GreeterClient(Connect *conn, const int &Interval_, QObject *parent = nullptr);
    virtual ~GreeterClient();
    virtual void request()=0;
    virtual void show(const QVariant & val)=0;
    QTimer timer;
signals:
    void resultReady(const QVariant &);
    void start();
    void stop();
public slots:
    virtual void reset();

private:

protected:
    //virtual void _reset();
    //std::unique_ptr<Greeter::Stub> stub_;
    Connect *conn_;
    int Interval;


};

#endif // GREETER_H
