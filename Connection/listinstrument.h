#ifndef LISTINSTRUMENT_H
#define LISTINSTRUMENT_H

#include "greeter.h"
#include <QVector>
#include <QDebug>
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;

using console::Request;
using console::Instrument;
Q_DECLARE_METATYPE(Instrument *)
class ListInstrument :public GreeterClient
{
    Q_OBJECT
public:
    explicit ListInstrument(Connect *conn,const int &Interval = 5000,
                             QObject *parent = nullptr);
    ~ListInstrument();

public slots:
    void request();
    void show(const QVariant & Online);


    void read(const QVariant &insName);

    void ShowOnline();
    void ShowList();
    void Search(const QVariant & key);
signals:
    void resultReady(const QVariant &);

private:

    QHash<QString ,Instrument *> ListIns;
    QVector<Instrument *> OnlineIns;

    std::unique_ptr<ClientReader<Instrument>> response_reader;
    void HandleDate(const console::Instrument &reply);


protected:
    void _reset();

};

#endif // LISTINSTRUMENT_H
