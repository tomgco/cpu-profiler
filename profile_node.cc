#include "profile_node.h"

namespace nodex {
  using v8::CpuProfileNode;
  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Handle;
  using v8::HandleScope;
  using v8::Integer;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::ObjectTemplate;
  using v8::Persistent;
  using v8::PropertyCallbackInfo;
  using v8::String;
  using v8::ThrowException;
  using v8::Undefined;
  using v8::Value;

  Persistent<ObjectTemplate> ProfileNode::node_template_;

  void ProfileNode::Initialize (Isolate* isolate) {
    Local<ObjectTemplate> o = ObjectTemplate::New();
    o->SetInternalFieldCount(1);
    o->SetAccessor(String::New("functionName"), ProfileNode::GetFunctionName);
    o->SetAccessor(String::New("scriptName"), ProfileNode::GetScriptName);
    o->SetAccessor(String::New("bailoutReason"), ProfileNode::GetBailoutReason);
    o->SetAccessor(String::New("lineNumber"), ProfileNode::GetLineNumber);
    o->SetAccessor(String::New("callUid"), ProfileNode::GetCallUid);
    o->SetAccessor(String::New("id"), ProfileNode::GetNodeId);
    o->SetAccessor(String::New("childrenCount"), ProfileNode::GetChildrenCount);
    o->SetAccessor(String::New("hitCount"), ProfileNode::GetHitCount);
    o->SetAccessor(String::New("scriptId"), ProfileNode::GetScriptId);
    o->Set(String::New("getChild"), FunctionTemplate::New(ProfileNode::GetChild));
    node_template_.Reset(isolate, o);
  }

  void ProfileNode::GetFunctionName (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    Handle<String> fname = static_cast<CpuProfileNode*>(ptr)->GetFunctionName();
    info.GetReturnValue().Set(fname);
  }

  void ProfileNode::GetScriptName (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    Handle<String> sname = static_cast<CpuProfileNode*>(ptr)->GetScriptResourceName();
    info.GetReturnValue().Set(sname);
  }

  void ProfileNode::GetBailoutReason (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    const char* breason_ptr = static_cast<CpuProfileNode*>(ptr)->GetBailoutReason();
    Handle<String> breason = v8::String::New(breason_ptr);
    info.GetReturnValue().Set(breason);
  }

  void ProfileNode::GetLineNumber (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int32_t ln = static_cast<CpuProfileNode*>(ptr)->GetLineNumber();
    info.GetReturnValue().Set(ln);
  }

  void ProfileNode::GetCallUid (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    uint32_t uid = static_cast<CpuProfileNode*>(ptr)->GetCallUid();
    info.GetReturnValue().Set(uid);
  }

  void ProfileNode::GetNodeId (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    uint32_t uid = static_cast<CpuProfileNode*>(ptr)->GetNodeId();
    info.GetReturnValue().Set(uid);
  }

  void ProfileNode::GetScriptId (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int sid = static_cast<CpuProfileNode*>(ptr)->GetScriptId();
    info.GetReturnValue().Set(Integer::New(sid));
  }

  void ProfileNode::GetChildrenCount (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int32_t count = static_cast<CpuProfileNode*>(ptr)->GetChildrenCount();
    info.GetReturnValue().Set(count);
  }

  void ProfileNode::GetHitCount (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    uint32_t hcount = static_cast<CpuProfileNode*>(ptr)->GetHitCount();
    info.GetReturnValue().Set(hcount);
  }

  void ProfileNode::GetChild (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    if (args.Length() < 1) {
      ThrowException(Exception::Error(String::New("No index specified")));
      return;
    } else if (!args[0]->IsInt32()) {
      ThrowException(Exception::Error(String::New("Argument must be integer")));
      return;
    }
    int32_t index = args[0]->Int32Value();
    Handle<Object> self = args.This();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    const CpuProfileNode* node = static_cast<CpuProfileNode*>(ptr)->GetChild(index);
    args.GetReturnValue().Set(ProfileNode::New(isolate, node));
  }

  Handle<Value> ProfileNode::New (Isolate* isolate, const CpuProfileNode* node) {
    if (node_template_.IsEmpty()) {
      ProfileNode::Initialize(isolate);
    }

    if(!node) {
      return Undefined();
    }
    else {
      Local<ObjectTemplate> tpl = Local<ObjectTemplate>::New(isolate, node_template_);
      Local<Object> obj = tpl->NewInstance();
      obj->SetAlignedPointerInInternalField(0, const_cast<CpuProfileNode*>(node));
      return obj;
    }
  }
}
