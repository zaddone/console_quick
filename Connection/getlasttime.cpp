#include "getlasttime.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QDateTime>
//#include <QQuickItem>

work::work(const int &timeOut_, QObject *parent):QThread(parent){

    //timer = new QTimer(this);
    //glt = parent;
    this->timeOut_ = timeOut_;
    this->timing_ = 0;
    //qDebug()<<timeOut_;
    //timer2.moveToThread(this);
    //timer2.setInterval(timeOut_);
    //QObject::connect(&timer2, SIGNAL(timeout()), this, SIGNAL(timeOut()), Qt::DirectConnection );
    //QObject::connect(this,&QThread::finished,&timer2,&QTimer::stop,Qt::DirectConnection );
    //QObject::connect(this,SIGNAL(startTimer()),&timer2,SLOT(start()),Qt::DirectConnection );
    //QObject::connect(this,SIGNAL(stopTimer()),&timer2,SLOT(stop()),Qt::DirectConnection );
    /**
    //this->moveToThread(&this->workerThread);
    timer.setInterval(1000/24);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(read()) );
    QObject::connect(this,SIGNAL(start()),&timer,SLOT(start()));
    QObject::connect(this,SIGNAL(stop()),&timer,SLOT(stop()));
    this->workerThread.start();
    **/
    timer.moveToThread(this);
    timer.setInterval(frameRate);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(read()), Qt::DirectConnection );
    QObject::connect(this,&QThread::finished,&timer,&QTimer::stop,Qt::DirectConnection );

}
work::~work(){

    mutex.lock();
    for (int i = 0;i<List.length();i++){
        delete List.at(i).value<LastTime*>();
    }
    List.clear();
    mutex.unlock();
}

void work::writeList(LastTime &lt){

    //this->timer2.stop();
    //this->timer2.start();
    //emit this->startTimer();
    //emit this->timeOut();
    this->timing_= 0;
    mutex.lock();
    int Len = List.length();
    if (Len == 0) {
        LastTime * nlt = new LastTime();
        nlt->CopyFrom(lt);
        List.append(QVariant::fromValue(nlt));
        mutex.unlock();
        return;
    }
    LastTime* lta;
    int d;
    for (int i = 0;i<Len;i++){
        lta = List.at(i).value<LastTime*>();
        d = lta->scale()-lt.scale();

        if (d==0){
            lta->CopyFrom(lt);
            //delete lt;
            mutex.unlock();
            return;
        }else if (d>0) {
            LastTime * nlt = new LastTime();
            nlt->CopyFrom(lt);
            //List.append(QVariant::fromValue(nlt));
            List.insert(i,QVariant::fromValue(nlt));
            mutex.unlock();
            return;
        }
    }
    LastTime * nlt = new LastTime();
    nlt->CopyFrom(lt);
    List.append(QVariant::fromValue(nlt));
    mutex.unlock();

}
void work::read(){
    //qDebug()<<"run write";
    this->timing_++;
    if (!checkTimeOut()){
        qDebug()<<"time Out";
        emit timeOut();
        this->timer.stop();
        return;
    }

    mutex.lock();
    LastTime* lta;
    for (int i = 0;i<List.length();i++){
        lta = List.at(i).value<LastTime*>();
        //if (i==0 ) qDebug() << QDateTime::fromTime_t((int)lta->time()).toString();
        emit write(i, QDateTime::fromTime_t((int)lta->time()).toString());
    }
    mutex.unlock();
}

bool work::checkTimeOut(){
    return ( this->timing_*frameRate < this->timeOut_ ) ;
}

void work::run(){

    timer.start();
    //timer2.start();
    exec();
    return;

}

GetLastTime::GetLastTime(Connect *conn, const int & Interval, QObject *parent):
    GreeterClient(conn,Interval,parent)
{

    //this->moveToThread(workerThread);
    //workerThread.start();
    //this->Interval
    qRegisterMetaType<LastTime>("LastTime&");
    window  = qobject_cast<QQuickWindow*>(conn->Engine_->rootObjects().at(0));
    QQuickItem *root = window->contentItem();
    QQmlComponent component(conn->Engine_, QUrl(QStringLiteral("qml/LastTime.qml")));
    childItem = qobject_cast<QQuickItem*>(component.create());
    
    QQmlEngine::setObjectOwnership(childItem, QQmlEngine::CppOwnership);

    childItem->setParentItem(root);
    childItem->setParent(conn->Engine_);
    LastTimeStart = false;

    childItem->setProperty("visible", false);
    QObject::connect(childItem,SIGNAL(closeLastTime()),this,SLOT(close()),Qt::DirectConnection);
    //QObject::connect(this,SIGNAL(read(QVariant,QVariant)),childItem,SLOT(updateShowModel(QVariant,QVariant)));

    //t =  new timeOut(Interval);
    //QObject::connect(t,SIGNAL(reset()),this,SLOT(reset()));


}
void GetLastTime::close(){
    //qDebug()<<"1close";
    LastTimeStart = false;
    qDebug()<<"close";
    //emit w->stop();
    if (w != nullptr){
        w->quit();
        w->wait();
        delete w;
        w = nullptr;
    }

}
GetLastTime::~GetLastTime(){
    //delete w;
    LastTimeStart = false;
    if (w != nullptr){
        //w->quit();
        //w->wait();
        delete w;
        w = nullptr;
    }
}
void GetLastTime::reset(){
    qDebug()<<"reset1";
    LastTimeStart = false;
    this->response_reader.reset();
    this->thread()->terminate();
    this->thread()->start();
    //this->response_reader.release();
    close();
    childItem->setProperty("visible", false);
    qDebug()<<"reset";
}
void GetLastTime::request()
{

   // gpr_timespec timespec;
   //   timespec.tv_sec = Interval/1000;
   //   timespec.tv_nsec = 0;
   //   timespec.clock_type = GPR_TIMESPAN;

   // ClientContext context;
   //   context.set_deadline(timespec);

    InstrumentSimple _request;

    _request.set_name(this->InsName.toStdString());
    LastTime response;
    ClientContext context;
    //emit t->start();
    std::unique_ptr<ClientReader<LastTime> > reader(
        this->conn_->stub_->GetLastTime(&context, _request));

    response_reader.swap(reader);
    while (response_reader->Read(&response) && this->LastTimeStart) {
        emit write(response);
        //response_reader->
        //w->writeList(response);
    }
    if (!this->LastTimeStart){
        qDebug()  << "stop." ;
        //delete reader;
        response_reader.reset();
        //reader->
        return;
    }

    Status status = response_reader->Finish();
    if (status.ok()) {
      qDebug()  << "rpc succeeded." ;
    } else {
      qDebug()  << "rpc failed." ;
    }
    if (this->LastTimeStart){
        this->request();
    }

}

void GetLastTime::show(const QVariant & val)
{
    //view->show();
    QObject * edit = window->findChild<QObject*>("edit");

    if (!edit){
        qErrnoWarning("edit find not");
    }

    int height = edit->property("height").value<int>();
    //qDebug() << height << "end";
    childItem->setProperty("fontPixelSize",height - edit->property("y").value<int>());
    childItem->setProperty("itemHeight",height*2);
    childItem->setProperty("itemWidth",edit->property("width"));
    childItem->setProperty("title", val);
    childItem->setProperty("visible", true);

    InsName = val.value<QString>();
    LastTimeStart = true;

    w = new work(this->Interval);
    //QObject::connect(this->w,SIGNAL(write(QVariant,QVariant)),this,SIGNAL(read(QVariant,QVariant)));
    QObject::connect(this->w,SIGNAL(write(QVariant,QVariant)),childItem,SLOT(updateShowModel(QVariant,QVariant)));
    QObject::connect(this->w,SIGNAL(timeOut()),this,SLOT(reset()),Qt::DirectConnection);
    QObject::connect(this,SIGNAL(write(LastTime&)),w,SLOT(writeList(LastTime&)),Qt::DirectConnection);


    w->start();

    QTimer::singleShot(0,this,SLOT(request()));
    qDebug()<<"show"<<InsName;

    //QTimer::singleShot(0,this,SLOT(request()));
    /**
    childItem =  this->conn_->qmlRoot->findChild<QQuickItem*>("myLoader");
    childItem->setProperty("source", "qml/LastTime.qml");

    QObject * edit = this->conn_->qmlRoot->findChild<QObject*>("edit");
    if (edit){
        childItem->setProperty("fontPixelSize",edit->property("font.pixelSize"));
        childItem->setProperty("itemHeight",edit->property("height"));
        childItem->setProperty("itemWidth",edit->property("width"));
    }
    **/

}
