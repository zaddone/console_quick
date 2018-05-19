#include "getlasttime.h"

GetLastTime::GetLastTime(Connect *conn, const int &Interval, QObject *parent):
    GreeterClient(conn,Interval,parent)
{
    QObject::connect(this,SIGNAL(resultReady(QVariant)),conn,SIGNAL(resultReady(QVariant)));
}
void GetLastTime::_reset(){
    qDebug()  << "ListInstrument reset." ;
    this->response_reader.reset();
}
