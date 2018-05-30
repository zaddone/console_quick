#ifndef GETLASTTIME_H
#define GETLASTTIME_H
#include "greeter.h"
#include <QQuickItem>
#include <QQuickWindow>
#include <QMutex>
#include <QThread>
//#include <QTimer>
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using console::InstrumentSimple;
using console::LastTime;
Q_DECLARE_METATYPE(LastTime)
Q_DECLARE_METATYPE(LastTime *)
const int frameRate = 1000/10;

class work : public QThread
{
    Q_OBJECT
    QMutex mutex;
    QTimer timer;




public:
    explicit work(const int & timeOut_, QObject *parent = nullptr);
    ~work();

    void run() override;
    //QTimer timer2;

    //void run();
    //GetLastTime *glt;

public slots:
    void read();
    void writeList(LastTime &lt);
    //void reset();


signals:
    //void resultReady(const QString &s);
    void write(const QVariant & i,const QVariant & val);
    void timeOut();
    //void startTimer();
    //void stopTimer();

private:

    QVector<QVariant> List;
    int timing_;
    int timeOut_;
    bool checkTimeOut();
};

class GetLastTime : public GreeterClient
{
    Q_OBJECT

    //
public:
    explicit GetLastTime(Connect *conn,const int &Interval = 5000,
                         QObject *parent = nullptr);
    ~GetLastTime();
public slots:
    void request();
    void show(const QVariant & val);
    void close();
    void reset();

signals:
    void resultReady(const QVariant &);
    //void start();
    //void stop();
    void write(LastTime &lt);
    //void read(const QVariant & i,const QVariant & val);

private:
    std::unique_ptr<ClientReader<LastTime>> response_reader;
    //QObject *item;
    QQuickItem *childItem;
    QQuickWindow *window;
    QString InsName;

    work * w;
    //timeOut * t;
    bool LastTimeStart;
protected:


};

#endif // GETLASTTIME_H
