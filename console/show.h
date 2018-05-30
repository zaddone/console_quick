#ifndef SHOW_H
#define SHOW_H

#include <QObject>
#include <QThread>
#include <QHash>
//#include "connect.h"
#include <QQmlApplicationEngine>
#include "../Connection/connection.h"
//#include "listinstrument.h"

//Q_DECLARE_METATYPE(GreeterClient)
//void (*InputHandleFunc)(GreeterClient * obj,const QString & key);
//class clientList {
//    ListInstrument *List;
//};
class InputHandleClass:public QObject {
    Q_OBJECT
signals:
    void Handle(const QVariant &t);
    void Handle();
    void Set(const QVariant &t);

public:
    explicit InputHandleClass(QObject *parent = nullptr);
    void run(const QVariant &t);
    void run();

private:

};

class Show : public QObject
{
    Q_OBJECT

public:
    explicit Show(QQmlApplicationEngine *Engine,const std::shared_ptr< ::grpc::ChannelInterface>&_channel, QObject *parent = nullptr);
    Q_INVOKABLE void HandleInput(const QVariant & state);
    //Q_INVOKABLE void CloseLastTime();
    ~Show();
    QThread workerThread;
    void Start();

signals:
    void resultReady(const QVariant &);

public slots:
    //void request();
    void run();
private:
    //struct clientList{
    //    ListInstrument List;
    //} clientList;
    //QHash<QString,GreeterClient *> clientList;

    //QObject * qmlRoot;
    GreeterClient * TmpClient;

    Connect con;
    Connection *connlib;

    QHash<QString,InputHandleClass *> InputRoute;
    void InitInputRoute();

    InputHandleClass *tmpHand;


};

#endif // SHOW_H
