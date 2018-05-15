#include <QtQml>
#include "view.h"
//#include <QtConcurrent>
#include "showlist.h"


View::View(QQmlApplicationEngine *view, std::shared_ptr<Channel> channel, QObject *parent) :
    Client(channel,parent)
{


    qmlView = view;
    qmlView->rootContext()->setContextProperty("view", this);
    //qmlView->setContextProperty("view", this);

    //workerThread = new QThread();
    this->moveToThread(&workerThread);
    workerThread.start();
    //QTimer::singleShot(0,this,SLOT(GetInstrument()));
    //QtConcurrent::run(this,&View::GetInstrument);
    QList<QObject *>ql =  qmlView->rootObjects();
    qmlRoot = NULL;
    for (int i = 0;i<ql.length();i++){
        if (ql[i]->objectName() == "myRect"){
            qmlRoot = ql[i];
            QObject::connect(this,SIGNAL(resultReady(QVariant)),qmlRoot,SLOT(appendModel(QVariant)),Qt::QueuedConnection);
            break;
        }

    }
    //if (!qmlRoot)

    //QObject::connect(this,SIGNAL(resultReady(QVariant)),qmlView,SLOT(appendModel(QVariant)),Qt::QueuedConnection);
    //QObject::connect(this,SIGNAL(resultReady(QVariant)),qmlView->rootObject(),SLOT(appendModel(QVariant)),Qt::QueuedConnection);
    //QEventLoop loop;
    QTimer::singleShot(0,this,SLOT(GetInstrument()));
    //QtConcurrent::run(this,&View::GetInstrument);
    //GetInstrument();
    //QObject::connect(workerThread
    tmpShow = NULL;
    //workerThread->start();
}
View::~View()
{
    if (this->tmpShow != NULL){
        delete this->tmpShow;
    }
    //delete workerThread;
    workerThread.quit();
    workerThread.wait();
}
void View::SetTmpShow(QObject * tmp){
    if (this->tmpShow != NULL){
        delete this->tmpShow;
    }
    this->tmpShow = tmp;
}
void View::CloseLastTime(){
    this->SetLastTimeStart(false);
    this->ClearTmpShow();
}

void View::ClearTmpShow(){
    if (this->tmpShow != NULL){
        delete this->tmpShow;
        this->tmpShow = NULL;
    }
}
void View::HandleInput(const QVariant & state){
    const QString & val = state.value<QString>().toUpper();
    if (val == "ONLINE"){
        this->ShowOnline();
    }else{
        const QStringList vallist = val.split(" ");
        if (vallist.count()==1)  SearchIns(val);
        else if (vallist[1] == "SEE") {
            ReadIns(vallist[0]);
        }else if (vallist[1] == "START") {
            StartIns(vallist[0]);
        }else if (vallist[1] == "SHOW") {
            //this->qmlObject->children()
            //qmlObject->
            if (this->qmlRoot){
                QObject * tmpObject = this->qmlRoot->findChild<QObject*>("showWindows");
                if (tmpObject) {
                    tmpObject->setProperty("visible", true);
                    ShowList *Show = new ShowList(vallist[0]);
                    this->SetTmpShow(Show);
                    QObject::connect(Show,&ShowList::setStart,this,&View::SetLastTimeStart, Qt::QueuedConnection);
                    QObject::connect(Show,&ShowList::read,this,&View::GetLastTime , Qt::QueuedConnection);
                    QObject::connect(this,&View::UpdateReady,Show,&ShowList::writeList, Qt::QueuedConnection);
                    QObject::connect(Show,SIGNAL(write(QVariant,QVariant)),tmpObject,SLOT(updateShowModel(QVariant,QVariant)),Qt::QueuedConnection);
                    QTimer::singleShot(0,Show,SLOT(runRead()));
                }
            }
        }
    }
}

//void View::GetLastTime(){
//    Client::GetLastTime(this->ShowInsName,this->tmpList);
    //this->GetLastTime()
//}
void View::GetInstrument(){
    //std::cout<<"ins run"<<std::endl;
    bool out = false;
    while(!out)out = listInstrument();
    this->ShowOnline();

}
