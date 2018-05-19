#include "connect.h"

Connect::Connect(const std::string &addr) :
    stub_(console::Greeter::NewStub(grpc::CreateChannel(addr,grpc::InsecureChannelCredentials())))
{

}

Connect::~Connect(){
    stub_.release();
}
