#include "startinstrument.h"

StartInstrument::StartInstrument(Connect *conn,const int &Interval, QObject *parent) :
    GreeterClient(conn,0,parent)
{
    this->Interval_ = Interval;
    //QObject::connect(this,&StartInstrument::resultReady ,conn,&Connect::resultReady ,Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(resultReady(QVariant)),conn,SIGNAL(resultReady(QVariant)));
}
void StartInstrument::SetInsName(const QString & name){
    this->InsName = name;
}
void StartInstrument::show(const QVariant & val){
    this->SetInsName(val.value<QString>());
    //qDebug()<<"show"<< this->InsName;
    this->request();
}
void StartInstrument::request(){
    //ClientContext context;

    gpr_timespec timespec;
      timespec.tv_sec = Interval_/1000;
      timespec.tv_nsec = 0;
      timespec.clock_type = GPR_TIMESPAN;

    ClientContext context;
      context.set_deadline(timespec);
    //context

    InstrumentSimple req;
    req.set_name(InsName.toStdString());
    InstrumentReply response;
    Status status = this->conn_->stub_->StartInstrument(&context, req, &response);
    if (!status.ok()) {
        emit resultReady(QVariant(QString::fromStdString(status.error_message())));
        return;
    }
    if (!response.state()){
        emit resultReady(QVariant(QString("response fail")));
        return;
    }
    emit resultReady(QVariant(QString("response success")));
    return;
}
