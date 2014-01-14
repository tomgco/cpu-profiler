#include "cpu_profiler.h"
#include "profile.h"
#include "node.h"

namespace nodex {
  using v8::CpuProfile;
  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::Handle;
  using v8::HandleScope;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::ThrowException;
  using v8::Value;

  CpuProfiler::CpuProfiler () {}
  CpuProfiler::~CpuProfiler () {}

  void CpuProfiler::Initialize (Isolate* isolate, Handle<Object> target) {
    HandleScope scope(isolate);
    NODE_SET_METHOD(target, "getProfilesCount", CpuProfiler::GetProfilesCount);
    NODE_SET_METHOD(target, "getProfile", CpuProfiler::GetProfile);
    NODE_SET_METHOD(target, "startProfiling", CpuProfiler::StartProfiling);
    NODE_SET_METHOD(target, "stopProfiling", CpuProfiler::StopProfiling);
    NODE_SET_METHOD(target, "deleteAllProfiles", CpuProfiler::DeleteAllProfiles);
  }

  void CpuProfiler::GetProfilesCount (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    args.GetReturnValue().Set(isolate->GetCpuProfiler()->GetProfileCount());
  }

  void CpuProfiler::GetProfile (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    if (args.Length() < 1) {
      ThrowException(Exception::Error(String::New("No index specified")));
      return;
    } else if ( ! args[0]->IsInt32()) {
      ThrowException(Exception::TypeError(String::New("Argument must be an integer")));
      return;
    }
    int32_t index = args[0]->Int32Value();
    const CpuProfile* profile = isolate->GetCpuProfiler()->GetCpuProfile(index);
    args.GetReturnValue().Set(Profile::New(isolate, profile));
  }

  void CpuProfiler::StartProfiling (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    Local<String> title =
        args.Length() > 0 ? args[0]->ToString() : String::Empty(isolate);
    bool recsamples =
        args.Length() > 1 ? args[1]->ToBoolean()->Value() : false;
    isolate->GetCpuProfiler()->StartCpuProfiling(title, recsamples);
    args.GetReturnValue().SetUndefined();
  }

  void CpuProfiler::StopProfiling (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    Local<String> title =
        args.Length() > 0 ? args[0]->ToString() : String::Empty(isolate);
    const CpuProfile* profile = isolate->GetCpuProfiler()->StopCpuProfiling(title);
    args.GetReturnValue().Set(Profile::New(isolate, profile));
  }

  void CpuProfiler::DeleteAllProfiles (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    isolate->GetCpuProfiler()->DeleteAllCpuProfiles();
    args.GetReturnValue().SetUndefined();
  }
} //namespace nodex
