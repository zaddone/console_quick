#ifndef VIEW_H
#define VIEW_H
#include "client.h"
#include<QQuickView>
#include<QTimer>
#include<QQmlApplicationEngine>

class View : public Client
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit View(QQmlApplicationEngine *view, std::shared_ptr<Channel> channel, QObject *parent = 0);
    Q_INVOKABLE void HandleInput(const QVariant & state);
    Q_INVOKABLE void CloseLastTime();
    ~View();

private:


    //QString ShowInsName;
    //QVector<LastTime*> tmpList;
    QQmlApplicationEngine *qmlView;
    QObject * qmlRoot;
    //void GetLastTime();
    QObject * tmpShow;
    void SetTmpShow(QObject * tmp);
    void ClearTmpShow();


signals:

    void resultReady(const QVariant & tag,const QVariant & time,const QVariant & scale);

public slots:
    void GetInstrument();
    //void GetLastTime();

};

#endif // VIEW_H
