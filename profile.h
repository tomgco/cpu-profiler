#ifndef NODE_PROFILE_
#define NODE_PROFILE_

#include <v8-profiler.h>

using namespace v8;

namespace nodex {

class Profile {
 public:
  static Handle<Value> New(Isolate* isolate, const CpuProfile* profile);
 
 private:
  static void GetUid(Local<String> property, const PropertyCallbackInfo<Value>& info);
  static void GetTitle(Local<String> property, const PropertyCallbackInfo<Value>& info);
  static void GetTopRoot(Local<String> property, const PropertyCallbackInfo<Value>& info);
  static void Delete(const FunctionCallbackInfo<Value>& args);
  static void Initialize(Isolate* isolate);
  static Persistent<ObjectTemplate> profile_template_;
};

} //namespace nodex
#endif  // NODE_PROFILE_
