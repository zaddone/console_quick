#include "greeter.h"

GreeterClient::GreeterClient(Connect *conn,const int & Interval_, QObject *parent) :
    QObject(parent)
{
    this->conn_ = conn;
    Interval = Interval_;
    if (Interval>0){
        this->timer.setInterval(Interval);
        this->timer.setSingleShot(false);
        QObject::connect(&this->timer,SIGNAL(timeout()),this,SLOT(reset()), Qt::QueuedConnection);

        QObject::connect(this,SIGNAL(start()),&timer,SLOT(start()), Qt::QueuedConnection);
        QObject::connect(this,SIGNAL(stop()),&timer,SLOT(stop()), Qt::QueuedConnection);
        //timer.stop();
        //this->workerThread.start();
    }
}
//void GreeterClient::_reset(){
//
//}

void GreeterClient::reset(){
    qDebug()<<"reset f";
    //this->workerThread.terminate();
    //this->_reset();
}
GreeterClient::~GreeterClient(){

}
