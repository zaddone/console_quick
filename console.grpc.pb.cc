// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: console.proto

#include "console.pb.h"
#include "console.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace console {

static const char* Greeter_method_names[] = {
  "/console.Greeter/ListInstrument",
  "/console.Greeter/StartInstrument",
  "/console.Greeter/GetLastTime",
};

std::unique_ptr< Greeter::Stub> Greeter::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Greeter::Stub> stub(new Greeter::Stub(channel));
  return stub;
}

Greeter::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_ListInstrument_(Greeter_method_names[0], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_StartInstrument_(Greeter_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetLastTime_(Greeter_method_names[2], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::ClientReader< ::console::Instrument>* Greeter::Stub::ListInstrumentRaw(::grpc::ClientContext* context, const ::console::Request& request) {
  return ::grpc::internal::ClientReaderFactory< ::console::Instrument>::Create(channel_.get(), rpcmethod_ListInstrument_, context, request);
}

::grpc::ClientAsyncReader< ::console::Instrument>* Greeter::Stub::AsyncListInstrumentRaw(::grpc::ClientContext* context, const ::console::Request& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::console::Instrument>::Create(channel_.get(), cq, rpcmethod_ListInstrument_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::console::Instrument>* Greeter::Stub::PrepareAsyncListInstrumentRaw(::grpc::ClientContext* context, const ::console::Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::console::Instrument>::Create(channel_.get(), cq, rpcmethod_ListInstrument_, context, request, false, nullptr);
}

::grpc::Status Greeter::Stub::StartInstrument(::grpc::ClientContext* context, const ::console::InstrumentSimple& request, ::console::InstrumentReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_StartInstrument_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::console::InstrumentReply>* Greeter::Stub::AsyncStartInstrumentRaw(::grpc::ClientContext* context, const ::console::InstrumentSimple& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::console::InstrumentReply>::Create(channel_.get(), cq, rpcmethod_StartInstrument_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::console::InstrumentReply>* Greeter::Stub::PrepareAsyncStartInstrumentRaw(::grpc::ClientContext* context, const ::console::InstrumentSimple& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::console::InstrumentReply>::Create(channel_.get(), cq, rpcmethod_StartInstrument_, context, request, false);
}

::grpc::ClientReader< ::console::LastTime>* Greeter::Stub::GetLastTimeRaw(::grpc::ClientContext* context, const ::console::InstrumentSimple& request) {
  return ::grpc::internal::ClientReaderFactory< ::console::LastTime>::Create(channel_.get(), rpcmethod_GetLastTime_, context, request);
}

::grpc::ClientAsyncReader< ::console::LastTime>* Greeter::Stub::AsyncGetLastTimeRaw(::grpc::ClientContext* context, const ::console::InstrumentSimple& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::console::LastTime>::Create(channel_.get(), cq, rpcmethod_GetLastTime_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::console::LastTime>* Greeter::Stub::PrepareAsyncGetLastTimeRaw(::grpc::ClientContext* context, const ::console::InstrumentSimple& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::console::LastTime>::Create(channel_.get(), cq, rpcmethod_GetLastTime_, context, request, false, nullptr);
}

Greeter::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Greeter_method_names[0],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Greeter::Service, ::console::Request, ::console::Instrument>(
          std::mem_fn(&Greeter::Service::ListInstrument), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Greeter_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Greeter::Service, ::console::InstrumentSimple, ::console::InstrumentReply>(
          std::mem_fn(&Greeter::Service::StartInstrument), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Greeter_method_names[2],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Greeter::Service, ::console::InstrumentSimple, ::console::LastTime>(
          std::mem_fn(&Greeter::Service::GetLastTime), this)));
}

Greeter::Service::~Service() {
}

::grpc::Status Greeter::Service::ListInstrument(::grpc::ServerContext* context, const ::console::Request* request, ::grpc::ServerWriter< ::console::Instrument>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Greeter::Service::StartInstrument(::grpc::ServerContext* context, const ::console::InstrumentSimple* request, ::console::InstrumentReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Greeter::Service::GetLastTime(::grpc::ServerContext* context, const ::console::InstrumentSimple* request, ::grpc::ServerWriter< ::console::LastTime>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace console

