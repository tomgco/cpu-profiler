#ifndef NODE_CPU_PROFILER_
#define NODE_CPU_PROFILER_

#include <v8-profiler.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace nodex {
  class CpuProfiler {
    public:
      static void Initialize(Isolate* isolate, Handle<Object> target);

      CpuProfiler();
      virtual ~CpuProfiler();

    protected:
      static void GetProfilesCount(const FunctionCallbackInfo<Value>& args);
      static void GetProfile(const FunctionCallbackInfo<Value>& args);
      static void StartProfiling(const FunctionCallbackInfo<Value>& args);
      static void StopProfiling(const FunctionCallbackInfo<Value>& args);
      static void DeleteAllProfiles(const FunctionCallbackInfo<Value>& args);
  };
} //namespace nodex

#endif  // NODE_CPU_PROFILER_H
