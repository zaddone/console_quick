#include "show.h"
InputHandleClass::InputHandleClass(QObject *parent): QObject(parent){

}
void InputHandleClass::run(const QVariant &t){
    emit this->Handle(t);
}
void InputHandleClass::run(){
    emit this->Handle();
}

Show::Show(QObject *qml, const QString &addr, QObject *parent) :
    QObject(parent),con(addr.toStdString())
{


    this->qmlRoot = qml;
    this->moveToThread(&this->workerThread);
    QObject::connect(this,SIGNAL(resultReady(QVariant)),qmlRoot,SLOT(appendModel(QVariant)),Qt::QueuedConnection);
    QObject::connect(&con,SIGNAL(resultReady(QVariant)),this,SIGNAL(resultReady(QVariant)),Qt::QueuedConnection);

    connlib = new Connection(&con);

    InitInputRoute();
    this->workerThread.start();
    TmpClient = connlib->listIns;
    QTimer::singleShot(0,this,SLOT(request()));
}
void Show::request(){
    TmpClient->request();
}
void Show::HandleInput(const QVariant & state){
    //const QString val = state.value<QString>().toUpper();
    const QStringList vallist = state.value<QString>().toUpper().split(" ");
    switch (vallist.length()) {
    case 1:
        {
            InputHandleClass *hand = this->InputRoute[vallist[0]];
            if (hand!=nullptr){
                emit this->resultReady(vallist[0]);
                hand->run();
            }else {
                //ListInstrument *lt = (ListInstrument *) clientList["ListInstrument"];
                this->connlib->listIns->Search(vallist[0]);
            }
            break;
        }
    case 2:
        {
            InputHandleClass *hand = this->InputRoute[vallist[1]];
            if (hand!=nullptr) {
                emit this->resultReady(state);
                hand->run(vallist[0]);
            }
            break;
        }
    case 0:
        this->InputRoute["ALL"]->run();
    }

    //emit this->resultReady(vallist[0]);
}
void Show::CloseLastTime(){

}
Show::~Show(){
    workerThread.quit();
    workerThread.wait();
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
    QObject::connect(SEE,SIGNAL(Handle(QVariant)),this->connlib->listIns,SLOT(read(QVariant)),Qt::QueuedConnection);
    this->InputRoute[QString("SEE")] = SEE;

    InputHandleClass *START  = new InputHandleClass();
    QObject::connect(START,SIGNAL(Handle(QVariant)),this->connlib->startIns,SLOT(show(QVariant)),Qt::QueuedConnection);
    this->InputRoute[QString("START")] = START;

}
