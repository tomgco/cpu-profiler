#include "cpu_profiler.h"
#include "node.h"

namespace nodex {
  using v8::Handle;
  using v8::Isolate;
  using v8::Object;

  void Initialize (Handle<Object> target) {
    // TODO(bnoordhuis) Isolate::GetCurrent() is about to be deprecated.
    // Replace with target->CreationContext()->GetIsolate() in due time
    // but not just yet - the symbol is missing from the v0.11.10 release
    // binary and it's anybody's guess when that will be fixed.  Track
    // https://github.com/joyent/node/issues/6801 for updates.
    Isolate* isolate = Isolate::GetCurrent();
    CpuProfiler::Initialize(isolate, target);
  }

  NODE_MODULE(profiler, Initialize)
}
