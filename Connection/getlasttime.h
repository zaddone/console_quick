#ifndef GETLASTTIME_H
#define GETLASTTIME_H
#include "greeter.h"

using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using console::InstrumentSimple;
using console::LastTime;

class GetLastTime : public GreeterClient
{
public:
    GetLastTime(Connect *conn,const int &Interval = 5000,
                QObject *parent = nullptr);
    ~GetLastTime();
public slots:
    void request();
    void show(const QVariant & Online);
signals:
    void resultReady(const QVariant &);

private:
    std::unique_ptr<ClientReader<LastTime>> response_reader;

protected:
    void _reset();
};

#endif // GETLASTTIME_H
