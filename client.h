#ifndef CLIENT_H
#define CLIENT_H

//#include <iostream>
//#include <memory>

//#include <string>
#include <QMetaType>
#include <QtCore>
#include <grpcpp/grpcpp.h>
#include "console.grpc.pb.h"
#include <QObject>
#include<QDebug>
#include <QtQuick/QQuickItem>
//#include <QtConcurrent>



using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using console::Greeter;
using console::Instrument;
using console::InstrumentSimple;
using console::InstrumentReply;
using console::LastTime;
Q_DECLARE_METATYPE(Instrument *)
Q_DECLARE_METATYPE(LastTime *)
Q_DECLARE_METATYPE(LastTime)

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(std::shared_ptr<Channel> channel,QObject *parent = 0);
    //Client(std::shared_ptr<Channel> channel);
    virtual ~Client();


protected:

    QVector<Instrument *> ListIns;
    QVector<Instrument *> OnlineIns;


    bool listInstrument();
    bool startInstrument(const std::string & name);

    void SearchIns(const QString & key);
    void ReadIns(const QString & key);
    void StartIns(const QString & insName);
    void ShowOnline();
    //void GetLastTime(const QString  & InsName, QVector<console::LastTime *> &listTime);
    //void GetLastTime(const QString  & InsName );
    //bool isOut;

private:
    std::unique_ptr<Greeter::Stub> stub_;

    void SordVector(QVector<LastTime *> &lt,int & index);



public slots:

    void GetLastTime(const QString  & InsName, bool *run);

    //void ShowLastTime();

signals:
    void resultReady(const QVariant & state);
    void UpdateReady(LastTime & lt);
    //void resultReady(const QVariant & state);
    //void resultReady(const QVariant & tag,const QVariant & time,const QVariant & scale);
    //void resultReady(const bool & start);
    //void ShowLastTime(const QString &,const QString & Tag,const long &  time);
};

#endif // CLIENT_H
