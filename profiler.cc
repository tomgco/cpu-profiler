#include "cpu_profiler.h"

namespace nodex {
  void Initialize (Handle<Object> target) {
    Isolate* isolate = target->CreationContext()->GetIsolate();
    CpuProfiler::Initialize(isolate, target);
  }

  NODE_MODULE(profiler, Initialize)
}
