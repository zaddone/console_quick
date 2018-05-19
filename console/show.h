#ifndef SHOW_H
#define SHOW_H

#include <QObject>
#include <QThread>
#include <QHash>
//#include "connect.h"
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
    explicit Show(QObject * qml,const QString & addr, QObject *parent = nullptr);
    Q_INVOKABLE void HandleInput(const QVariant & state);
    Q_INVOKABLE void CloseLastTime();
    ~Show();
    QThread workerThread;
    void Start();

signals:
    void resultReady(const QVariant &);

public slots:
    void request();
private:
    //struct clientList{
    //    ListInstrument List;
    //} clientList;
    //QHash<QString,GreeterClient *> clientList;

    QObject * qmlRoot;
    GreeterClient * TmpClient;

    Connect con;
    Connection *connlib;

    QHash<QString,InputHandleClass *> InputRoute;
    void InitInputRoute();


};

#endif // SHOW_H
