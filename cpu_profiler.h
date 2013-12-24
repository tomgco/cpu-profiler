#ifndef NODE_CPU_PROFILER_
#define NODE_CPU_PROFILER_

#include "v8-profiler.h"

namespace nodex {
  class CpuProfiler {
    public:
      static void Initialize(v8::Isolate* isolate, v8::Handle<v8::Object> target);

      CpuProfiler();
      virtual ~CpuProfiler();

    protected:
      static void GetProfilesCount(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void GetProfile(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void StartProfiling(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void StopProfiling(const v8::FunctionCallbackInfo<v8::Value>& args);
      static void DeleteAllProfiles(const v8::FunctionCallbackInfo<v8::Value>& args);
  };
} //namespace nodex

#endif  // NODE_CPU_PROFILER_H
