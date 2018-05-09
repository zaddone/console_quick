#ifndef VIEW_H
#define VIEW_H
#include "client.h"
#include<QQuickView>
#include<QTimer>

class View : public Client
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit View(QQuickView *view, std::shared_ptr<Channel> channel, QObject *parent = 0);
    Q_INVOKABLE void HandleInput(const QVariant & state);
    Q_INVOKABLE void ClearTmpShow();
    ~View();

private:


    //QString ShowInsName;
    //QVector<LastTime*> tmpList;
    QQuickView *qmlView;
    //void GetLastTime();
    QObject * tmpShow;
    void SetTmpShow(QObject * tmp);


signals:

    void resultReady(const QVariant & tag,const QVariant & time,const QVariant & scale);

public slots:
    void GetInstrument();
    //void GetLastTime();

};

#endif // VIEW_H
