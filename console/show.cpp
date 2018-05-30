#include "show.h"
InputHandleClass::InputHandleClass(QObject *parent): QObject(parent){

}
void InputHandleClass::run(const QVariant &t){
    emit this->Handle(t);
}
void InputHandleClass::run(){
    emit this->Handle();
}

Show::Show(QQmlApplicationEngine *Engine, const std::shared_ptr<::grpc::ChannelInterface> &_channel, QObject *parent) :
    QObject(parent),con(Engine,_channel)
{

    //con.qmlRoot = Engine;
    //this->qmlRoot = qml;
    QObject *qml = Engine->rootObjects().at(0);
    //this->moveToThread(&this->workerThread);
    QObject::connect(this,SIGNAL(resultReady(QVariant)),qml,SLOT(appendModel(QVariant)),Qt::QueuedConnection);
    QObject::connect(&con,SIGNAL(resultReady(QVariant)),this,SIGNAL(resultReady(QVariant)),Qt::QueuedConnection);
    QObject::connect(qml,SIGNAL(handleInput(QVariant)),this,SLOT(HandleInput(QVariant)),Qt::QueuedConnection);
    connlib = new Connection(&con,&this->workerThread);
    InitInputRoute();
    this->workerThread.start();
    //TmpClient = connlib->listIns;
    QTimer::singleShot(0,connlib->listIns,SLOT(request()));

}
void Show::run(){
    this->tmpHand->run();
}
/**
void Show::request(){
    TmpClient->request();
}
**/
void Show::HandleInput(const QVariant & state){
    //const QString val = state.value<QString>().toUpper();
    const QStringList vallist = state.value<QString>().toUpper().split(" ");
    switch (vallist.length()) {
    case 1:
        {
            tmpHand = this->InputRoute[vallist[0]];
            if (tmpHand!=nullptr){
                emit this->resultReady(vallist[0]);
                tmpHand->run();
            }else {
                //ListInstrument *lt = (ListInstrument *) clientList["ListInstrument"];
                this->connlib->listIns->Search(vallist[0]);
            }
            break;
        }
    case 2:
        {
            tmpHand = this->InputRoute[vallist[1]];
            if (tmpHand!=nullptr) {
                emit this->resultReady(state);
                tmpHand->run(vallist[0]);
            }
            break;
        }
    case 0:
        this->InputRoute["ALL"]->run();
    }

    //emit this->resultReady(vallist[0]);
}

Show::~Show(){
    //workerThread.quit();
    //workerThread.wait();
    workerThread.terminate();
    delete connlib;
}
void Show::InitInputRoute(){
    //ListInstrument *lt = this->connlib->listIns;
    InputHandleClass *All  = new InputHandleClass();

    QObject::connect(All,SIGNAL(Handle()),this->connlib->listIns,SLOT(ShowList()),Qt::QueuedConnection);
    this->InputRoute[QString("ALL")] = All;

    InputHandleClass *ONLINE  = new InputHandleClass();
    QObject::connect(ONLINE,SIGNAL(Handle()),this->connlib->listIns,SLOT(ShowOnline()),Qt::QueuedConnection);
    this->InputRoute[QString("ONLINE")] = ONLINE;

    InputHandleClass *SEE  = new InputHandleClass();
    //QObject::connect(SEE,SIGNAL(Set(QVariant)),this->connlib->listIns,SLOT(SetInsName(QVariant)),Qt::QueuedConnection);
    QObject::connect(SEE,SIGNAL(Handle(QVariant)),this->connlib->listIns,SLOT(read(QVariant)),Qt::QueuedConnection);
    this->InputRoute[QString("SEE")] = SEE;

    InputHandleClass *START  = new InputHandleClass();
    QObject::connect(START,SIGNAL(Handle(QVariant)),this->connlib->startIns,SLOT(show(QVariant)),Qt::QueuedConnection);
    this->InputRoute[QString("START")] = START;


    InputHandleClass *SHOW  = new InputHandleClass();
    //this->connlib->lastTime->sh
    //QObject::connect(SEE,SIGNAL(Set(QVariant)),this->connlib->lastTime,SLOT(SetInsName(QVariant)),Qt::QueuedConnection);
    QObject::connect(SHOW,SIGNAL(Handle(QVariant)),this->connlib->lastTime,SLOT(show(QVariant)),Qt::QueuedConnection);
    this->InputRoute[QString("SHOW")] = SHOW;



}
