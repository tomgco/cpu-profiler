#include "cpu_profiler.h"
#include "node.h"

namespace nodex {
  using v8::Handle;
  using v8::Isolate;
  using v8::Object;

  void Initialize (Handle<Object> target) {
    Isolate* isolate = target->CreationContext()->GetIsolate();
    CpuProfiler::Initialize(isolate, target);
  }

  NODE_MODULE(profiler, Initialize)
}
