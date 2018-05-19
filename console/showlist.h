#ifndef SHOWLIST_H
#define SHOWLIST_H
/**
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QMutex>
#include <QTimer>
#include <QDateTime>
//#include "client.h"
#include "Connection/console.grpc.pb.h"

using console::LastTime;
Q_DECLARE_METATYPE(LastTime *)

class ShowList : public QObject
{
    Q_OBJECT
    QMutex mutex;
    QTimer timer;
public:
    explicit ShowList(const QString &insName, QObject *parent = 0);
    ~ShowList();
signals:
    void read(const QString &insName);
    void write(QVariant,QVariant);
    void setStart(bool start);

public slots:
    void runRead();
    void writeList(LastTime & lt);
    void runWrite();
    //void close();
    //void show();

private:
    QString InsName;
    QVector<QVariant> List;
    //bool isRun;

};
**/
#endif // SHOWLIST_H
