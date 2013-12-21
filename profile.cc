#include "profile.h"
#include "profile_node.h"

using namespace v8;

namespace nodex {
  Persistent<ObjectTemplate> Profile::profile_template_;

  void Profile::Initialize (Isolate* isolate) {
    HandleScope scope(isolate);
    Local<ObjectTemplate> o = ObjectTemplate::New();
    o->SetInternalFieldCount(1);
    o->SetAccessor(String::New("title"), Profile::GetTitle);
    o->SetAccessor(String::New("uid"), Profile::GetUid);
    o->SetAccessor(String::New("topRoot"), Profile::GetTopRoot);
    o->Set(String::New("delete"), FunctionTemplate::New(Profile::Delete));
    profile_template_.Reset(isolate, o);
  }

  void Profile::GetUid (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    uint32_t uid = static_cast<CpuProfile*>(ptr)->GetUid();
    info.GetReturnValue().Set(Integer::NewFromUnsigned(uid));
  }


  void Profile::GetTitle (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    Handle<String> title = static_cast<CpuProfile*>(ptr)->GetTitle();
    info.GetReturnValue().Set(title);
  }

  void Profile::GetTopRoot (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    const CpuProfileNode* node = static_cast<CpuProfile*>(ptr)->GetTopDownRoot();
    info.GetReturnValue().Set(ProfileNode::New(isolate, node));
  }


  void Profile::Delete (const FunctionCallbackInfo<Value>& args) {
    HandleScope scope(args.GetIsolate());
    Handle<Object> self = args.This();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    static_cast<CpuProfile*>(ptr)->Delete();
    args.GetReturnValue().SetUndefined();
  }

  Handle<Value> Profile::New (Isolate* isolate, const CpuProfile* profile) {
    if (profile_template_.IsEmpty()) {
      Profile::Initialize(isolate);
    }
    
    if ( ! profile) {
      return Undefined();
    } else {
      Local<ObjectTemplate> tpl = Local<ObjectTemplate>::New(isolate, profile_template_);
      Local<Object> obj = tpl->NewInstance();
      obj->SetAlignedPointerInInternalField(0, const_cast<CpuProfile*>(profile));
      return obj;
    }
  }
}
