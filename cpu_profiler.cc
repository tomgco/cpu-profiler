#include "cpu_profiler.h"
#include "profile.h"

namespace nodex {
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
    isolate->GetCpuProfiler()->StartCpuProfiling(title);
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
