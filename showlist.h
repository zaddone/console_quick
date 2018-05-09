#ifndef SHOWLIST_H
#define SHOWLIST_H

#include <QObject>
#include <QVector>
#include <QVariant>
#include "client.h"

class ShowList : public QObject
{
    Q_OBJECT
    QMutex mutex;
    QTimer timer;
public:
    explicit ShowList(const QString &insName, QObject *parent = 0);
    ~ShowList();
signals:
    void read(const QString &insName,bool *run);
    void write(QVariant,QVariant);

public slots:
    void runRead();
    void writeList(LastTime & lt);
    void runWrite();
    //void show();

private:
    QString InsName;
    QVector<QVariant> List;
    bool isRun;

};

#endif // SHOWLIST_H
