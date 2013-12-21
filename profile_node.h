

#ifndef NODE_PROFILE_NODE_
#define NODE_PROFILE_NODE_

#include <v8-profiler.h>

using namespace v8;

namespace nodex {

class ProfileNode {
 public:
   static Handle<Value> New(Isolate* isolate, const CpuProfileNode* node);

 private:
   static void GetFunctionName(Local<String> property, const PropertyCallbackInfo<Value>& info);
   static void GetScriptName(Local<String> property, const PropertyCallbackInfo<Value>& info);
   static void GetLineNumber(Local<String> property, const PropertyCallbackInfo<Value>& info);
   static void GetCallUid(Local<String> property, const PropertyCallbackInfo<Value>& info);
   static void GetChildrenCount(Local<String> property, const PropertyCallbackInfo<Value>& info);
   static void GetChild(const FunctionCallbackInfo<Value>& args);
   static void Initialize(Isolate* isolate);
   static Persistent<ObjectTemplate> node_template_;
};

}
#endif  // NODE_PROFILE_NODE_
