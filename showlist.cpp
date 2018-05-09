#include "showlist.h"
#include <QThread>

ShowList::ShowList(const QString &insName,  QObject *parent) :
    QObject(parent)
{
    this->InsName = insName;
    this->List.reserve(30);
    timer.setInterval(1000/24);
    timer.start();
    //this->isRun = true;
    connect(&timer, SIGNAL(timeout()), this, SLOT(runWrite()),Qt::QueuedConnection);

}
ShowList::~ShowList() {

    this->isRun = false;
    timer.stop();
    mutex.lock();
    for (int i = 0;i<List.length();i++){
        delete List.at(i).value<LastTime*>();
    }

    List.clear();
    mutex.unlock();

    //workerRead.quit();
    //workerRead.wait();
}
void ShowList::runRead(){
    //while(isRun){
    this->isRun = true;
    emit this->read(this->InsName,&this->isRun);
    //}
}
void ShowList::runWrite(){
    mutex.lock();
    LastTime* lta;
    for (int i = 0;i<List.length();i++){
        lta = List.at(i).value<LastTime*>();
        emit write(i,QDateTime::fromTime_t((int)lta->time()).toString());
    }
    mutex.unlock();

}

void ShowList::writeList(LastTime &lt){

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
    //List.append(QVariant::fromValue(lt));
    mutex.unlock();
}
