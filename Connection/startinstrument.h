#ifndef STARTINSTRUMENT_H
#define STARTINSTRUMENT_H

#include "greeter.h"
#include<QVariant>
using grpc::ClientContext;
//using grpc::;
using grpc::Status;


using console::InstrumentSimple;
using console::InstrumentReply;

class StartInstrument : public GreeterClient
{
    Q_OBJECT
public:
    explicit StartInstrument(Connect *conn,const int &Interval = 5000,QObject *parent = nullptr);

signals:
    void resultReady(const QVariant &);
public slots:
    void request();
    void show(const QVariant & val);
    //void setVal(const QVariant & val);
    void SetInsName(const QString &name);
private:
    QString InsName;
    int Interval_;
};

#endif // STARTINSTRUMENT_H
