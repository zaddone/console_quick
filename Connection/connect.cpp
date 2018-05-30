#include "connect.h"

Connect::Connect(QQmlApplicationEngine *Engine, const std::shared_ptr<grpc::ChannelInterface> &_channel) :
    //stub_(console::Greeter::NewStub(grpc::CreateChannel(addr,grpc::InsecureChannelCredentials())))
    stub_(console::Greeter::NewStub(_channel))
{
    //channel = grpc::InsecureChannelCredentials();


    this->Engine_ = Engine;
}

Connect::~Connect(){
    stub_.release();
}
