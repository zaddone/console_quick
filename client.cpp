#include "client.h"
//#include "showwindows.h"
//#include <QtConcurrent>



Client::Client(std::shared_ptr<Channel> channel, QObject *parent):QObject(parent),stub_(Greeter::NewStub(channel))
{
    //console::AccountId
    //Thread = new WorkerThread();

    //this->qmlObject = root;
    //GetInstrument();
    //QObject::connect(workerThread,SIGNAL(started()),this,SLOT(GetInstrument()),Qt::QueuedConnection);
    //qRegisterMetaType<LastTime>("LastTime");
    qRegisterMetaType<LastTime>("LastTime&");
    //this->LastTimeStart = false;
    this->SetLastTimeStart(false);
    //qRegisterMetaType<bool>("bool*");
}

Client::~Client(){
    QVector<Instrument*>::iterator it;

    this->SetLastTimeStart(false);
    for(it=this->ListIns.begin();it!=this->ListIns.end();it++){
        delete (*it);
    }
    ListIns.clear();
    //for(it=this->OnlineIns.begin();it!=this->OnlineIns.end();it++){
    //    delete (*it);
    //}
    OnlineIns.clear();


}

bool Client::listInstrument()
{

    console::Request Request;
    Instrument instrument;
    ClientContext context;


    std::unique_ptr<ClientReader<Instrument> > reader(
        stub_->ListInstrument(&context, Request));
    while (reader->Read(&instrument)) {
        //printf("%p\n", instrument.);
        Instrument *ins = new Instrument();
        //Instrument *ins = instrument.New();
        ins->CopyFrom(instrument);
        if (instrument.online()){
            OnlineIns.append(ins);
        }
        ListIns.append(ins);

        //handfunc(&instrument,obj);
        /**
        QVariant v = QVariant::fromValue(ins);
        Instrument * _ins = v.value<Instrument*>();
         **/
      //std::cout << "Found AccountId called " << ins->name() << std::endl;

    }
    return reader->Finish().ok();
/**
    Status status = reader->Finish();
    if (status.ok()) {
      std::cout << "GetAccountId rpc succeeded." << std::endl;
    } else {
      std::cout << "GetAccountId rpc failed." << std::endl;
    }
**/
}

bool Client::startInstrument(const std::string &name){
    ClientContext context;
    InstrumentSimple request;
    request.set_name(name);
    InstrumentReply response;
    Status status = stub_->StartInstrument(&context, request, &response);
    if (!status.ok()) return false;
    if (!response.state()) return false;
    return true;
}

void Client::StartIns(const QString & key){
    for (int i=0;i<this->ListIns.length();i++){
        Instrument * it = this->ListIns.at(i);
        if (key == QString::fromStdString(it->name())){
            it->set_online(this->startInstrument(it->name()));
            emit resultReady(key+" start "+(it->online()?"Success":"failure"));
            return;
        }
    }
}
void Client::ReadIns(const QString & key){
    for (int i=0;i<this->ListIns.length();i++){
        Instrument * it = this->ListIns.at(i);
        if (key == QString::fromStdString(it->name())){

            emit resultReady("type:"+QString::fromStdString(it->type()));
            emit resultReady("DisplayPrecision:"+QString::number(it->displayprecision()));
            emit resultReady("MarginRate:"+QString::number(it->marginrate()));
            emit resultReady("MaximumOrderUnits:"+QString::number(it->maximumorderunits()));
            emit resultReady("MaximumPositionSize:"+QString::number(it->maximumpositionsize()));
            emit resultReady("MaximumTrailingStopDistance:"+QString::number(it->maximumtrailingstopdistance()));
            emit resultReady("MinimumTradeSize:"+QString::number(it->minimumtradesize()));
            emit resultReady("MinimumTrailingStopDistance:"+QString::number(it->minimumtrailingstopdistance()));
            emit resultReady("PipLocation:"+QString::number(it->piplocation()));
            emit resultReady("TradeUnitsPrecision:"+QString::number(it->tradeunitsprecision()));
            if (it->online())  emit resultReady("Online");

            emit resultReady(key);
            return;
        }
    }
}
void Client::SearchIns(const QString & key){
    QString  tmpstr;
    //TmpIns.clear();
    for (int i=0;i<this->ListIns.length();i++){
        Instrument * it = this->ListIns.at(i);
        tmpstr = QString::fromStdString(it->name());
        if (tmpstr.contains(key))
        {
            //TmpIns.append(it);
            emit resultReady(tmpstr);
        }
    }
}

void Client::ShowOnline(){
    for (int i=0;i<this->OnlineIns.length();i++){
        //std::cout<<OnlineIns.at(i)->name()<<std::endl;
        emit resultReady(QString::fromStdString(OnlineIns.at(i)->name()));
    }
    emit resultReady(QString("Online"));
}
void Client::SetLastTimeStart(const bool start){
    this->LastTimeStart = start;
    qDebug()<<"SetLastTimeStart "<< start;
}

void Client::GetLastTime(const QString &InsName)
{
    //isOut = true;
    InstrumentSimple request;
    request.set_name(InsName.toStdString());
    LastTime response;
    ClientContext context;
    std::unique_ptr<ClientReader<LastTime> > reader(
        stub_->GetLastTime(&context, request));
    while (reader->Read(&response) && this->LastTimeStart) {
        emit UpdateReady(response);
    }
    if (!this->LastTimeStart){
        qDebug()  << "stop." ;
        //delete reader;
        reader.reset();
        //reader->
        return;
    }

    //qDebug()  << run;
    //reader->clear();
    Status status = reader->Finish();
    if (status.ok()) {
      qDebug()  << "rpc succeeded." ;
    } else {
      qDebug()  << "rpc failed." ;
    }
    if (this->LastTimeStart){
        GetLastTime(InsName);
    }

}

