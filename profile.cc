#include "profile.h"
#include "profile_node.h"

namespace nodex {
  using v8::CpuProfile;
  using v8::CpuProfileNode;
  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::FunctionTemplate;
  using v8::Handle;
  using v8::HandleScope;
  using v8::Integer;
  using v8::Isolate;
  using v8::Local;
  using v8::Number;
  using v8::Object;
  using v8::ObjectTemplate;
  using v8::Persistent;
  using v8::PropertyCallbackInfo;
  using v8::String;
  using v8::ThrowException;
  using v8::Undefined;
  using v8::Value;

  Persistent<ObjectTemplate> Profile::profile_template_;

  void Profile::Initialize (Isolate* isolate) {
    HandleScope scope(isolate);
    Local<ObjectTemplate> o = ObjectTemplate::New();
    o->SetInternalFieldCount(1);
    o->SetAccessor(String::New("title"), Profile::GetTitle);
    o->SetAccessor(String::New("uid"), Profile::GetUid);
    o->SetAccessor(String::New("topRoot"), Profile::GetTopRoot);
    o->SetAccessor(String::New("startTime"), Profile::GetStartTime);
    o->SetAccessor(String::New("endTime"), Profile::GetEndTime);
    o->SetAccessor(String::New("samplesCount"), Profile::GetSamplesCount);
    o->Set(String::New("delete"), FunctionTemplate::New(Profile::Delete));
    o->Set(String::New("getSample"), FunctionTemplate::New(Profile::GetSample));
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

  void Profile::GetStartTime (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int64_t startTime = static_cast<CpuProfile*>(ptr)->GetStartTime();
    info.GetReturnValue().Set(Number::New(isolate, startTime));
  }

  void Profile::GetEndTime (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    Isolate* isolate = info.GetIsolate();
    HandleScope scope(isolate);
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int64_t endTime = static_cast<CpuProfile*>(ptr)->GetEndTime();
    info.GetReturnValue().Set(Number::New(isolate, endTime));
  }

  void Profile::GetSamplesCount (Local<String> property, const PropertyCallbackInfo<Value>& info) {
    HandleScope scope(info.GetIsolate());
    Local<Object> self = info.Holder();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int scount = static_cast<CpuProfile*>(ptr)->GetSamplesCount();
    info.GetReturnValue().Set(Integer::New(scount));
  }

  void Profile::GetSample (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);
    if (args.Length() < 1) {
      ThrowException(Exception::Error(String::New("No index specified")));
      return;
    } else if (!args[0]->IsInt32()) {
      ThrowException(Exception::Error(String::New("Argument must be integer")));
      return;
    }
    int index = args[0]->Int32Value();
    Handle<Object> self = args.This();
    void* ptr = self->GetAlignedPointerFromInternalField(0);
    int scount = static_cast<CpuProfile*>(ptr)->GetSamplesCount();
    // Samples have not been collected
    if (scount == 0) {
      ThrowException(Exception::Error(String::New("No sampels have been collected")));
      return;
    }
    // Check that the index is in range
    if (!(index >= 0 && index <= scount - 1)) {
      ThrowException(Exception::Error(String::New("Index is not in range of samplesCount")));
      return;
    }
    const CpuProfileNode* node = static_cast<CpuProfile*>(ptr)->GetSample(index);
    args.GetReturnValue().Set(ProfileNode::New(isolate, node));
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
