#ifndef NODE_PROFILE_
#define NODE_PROFILE_

#include "v8-profiler.h"

namespace nodex {

class Profile {
 public:
  static v8::Handle<v8::Value> New(v8::Isolate* isolate, const v8::CpuProfile* profile);
 
 private:
  static void GetUid(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetTitle(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetStartTime(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetEndTime(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetTopRoot(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetSamplesCount(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
  static void GetSample(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Delete(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Initialize(v8::Isolate* isolate);
  static v8::Persistent<v8::ObjectTemplate> profile_template_;
};

} //namespace nodex
#endif  // NODE_PROFILE_
