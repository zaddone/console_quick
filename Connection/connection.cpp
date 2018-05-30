#include "connection.h"


Connection::Connection(Connect *conn, QThread *th)
{

    listIns = new  ListInstrument(conn);
    listIns->moveToThread(th);

    startIns = new StartInstrument(conn);
    startIns->moveToThread(th);

    lastTime = new GetLastTime(conn);
    lastTime->moveToThread(th);

}
Connection::~Connection(){

    delete listIns;
    delete startIns;
    delete lastTime;

}
