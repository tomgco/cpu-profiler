#ifndef NODE_PROFILE_NODE_
#define NODE_PROFILE_NODE_

#include "v8-profiler.h"

namespace nodex {

class ProfileNode {
 public:
   static v8::Handle<v8::Value> New(v8::Isolate* isolate, const v8::CpuProfileNode* node);

 private:
   static void GetFunctionName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetScriptName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetBailoutReason(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetLineNumber(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetCallUid(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetNodeId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetChildrenCount(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetHitCount(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetScriptId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
   static void GetChild(const v8::FunctionCallbackInfo<v8::Value>& args);
   static void Initialize(v8::Isolate* isolate);
   static v8::Persistent<v8::ObjectTemplate> node_template_;
};

}
#endif  // NODE_PROFILE_NODE_
