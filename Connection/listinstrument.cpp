#include "listinstrument.h"

//using grpc::ClientContext;

ListInstrument::ListInstrument(Connect *conn, const int & Interval, QObject *parent):
    GreeterClient(conn,Interval,parent)
    //response_reader(stub_->ListInstrument(&this->context, req))
{
    //QObject::connect(this,&ListInstrument::resultReady ,conn,&Connect::resultReady ,Qt::QueuedConnection);
    QObject::connect(this,SIGNAL(resultReady(QVariant)),conn,SIGNAL(resultReady(QVariant)));
}

ListInstrument::~ListInstrument(){
    QHash<QString ,Instrument *>::iterator it;
    for(it=this->ListIns.begin();it!=this->ListIns.end();++it){
        delete (*it);
    }
    ListIns.clear();
    OnlineIns.clear();


    //this->timer.stop();
}
void ListInstrument::_reset(){
    qDebug()  << "ListInstrument reset." ;
    this->response_reader.reset();
}
void ListInstrument::show(const QVariant & Online){
    //qDebug()<<"show";
    if (Online.value<bool>())
        this->ShowOnline();
    else
        this->ShowList();
}
void ListInstrument::Search(const QVariant &key){
    QHash<QString ,Instrument *>::const_iterator it;
    for(it=this->ListIns.constBegin();it!=this->ListIns.constEnd();++it){
        if (it.key().contains(key.value<QString>())){
            emit this->resultReady(it.key());
        }
    }
}
void ListInstrument::ShowList(){
    QHash<QString ,Instrument *>::const_iterator it;
    for(it=this->ListIns.constBegin();it!=this->ListIns.constEnd();++it){
        emit this->resultReady(it.key());
    };
}

void ListInstrument::ShowOnline(){
    //qDebug()<<"online";
    for (int i=0;i<this->OnlineIns.length();i++){
        emit resultReady(QString::fromStdString(OnlineIns.at(i)->name()));
    }
}
void ListInstrument::HandleDate(const Instrument &reply){
    Instrument *ins = new Instrument();
    ins->CopyFrom(reply);
    if (reply.online()){
        OnlineIns.append(ins);
    }
    ListIns.insert(QString::fromStdString(ins->name()),ins);
    //ListIns.append(ins);
}
void ListInstrument::request(){

    //workerThread.start();
    ClientContext context;
    Request req;
    //timer.start();

    std::unique_ptr<ClientReader<Instrument>> reader(this->conn_->stub_->ListInstrument(&context, req));

    //qDebug()<<"start";
    //this->response_reader = std::move(reader);
    this->response_reader.swap(reader);
    emit this->start();
    //response_reader.
    Instrument reply;
    while (response_reader->Read(&reply)) {
        emit this->stop();
        HandleDate(reply);
        emit this->start();
    }
    emit this->stop();
    //qDebug()<<"stop";
    Status st = response_reader->Finish();
    if (! st.ok()){
        //this->workerThread.sleep(100);
        request();

    }else{
        this->show(true);
        //this->_stop();
    }

}
void ListInstrument::read(const QVariant &insName){
    Instrument * it = this->ListIns[insName.value<QString>()];
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
    if (it->online()) emit resultReady("Online");
}
