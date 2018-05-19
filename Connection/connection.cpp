#include "connection.h"


Connection::Connection(Connect *conn)
{
    listIns = new  ListInstrument(conn);
    startIns = new StartInstrument(conn);
}
Connection::~Connection(){
    delete listIns;
    delete startIns;

}
