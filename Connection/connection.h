#ifndef CONNECTION_H
#define CONNECTION_H
#include "listinstrument.h"
#include "startinstrument.h"
#include "getlasttime.h"
#include <QThread>

class Connection
{

public:
    Connection(Connect * conn,QThread *th);
    ~Connection();
    StartInstrument *startIns;
    ListInstrument *listIns;
    GetLastTime * lastTime;

};

#endif // CONNECTION_H
