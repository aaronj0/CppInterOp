#include "TestDownstreamLib.h"

#include "CppInterOp/Dispatch.h"

// Per-DSO slot storage, mirroring cppyy-backend's cppinterop_dispatch.cxx.
namespace CppInternal {
namespace DispatchRaw {
#define CPPINTEROP_API_FUNC(DN, CN, Ret, DeclArgs, CallArgs, RawTypes)         \
  Ret(*DN) RawTypes = nullptr;
#include "CppInterOp/CppInterOpAPI.inc"
} // namespace DispatchRaw
} // namespace CppInternal

// ODR-uses the inline JitCall fast path. JC is opaque so the optimizer
// can't DCE the calls at any -O level. The body never runs at test
// time; only the .o's UND-symbol surface matters.
void downstream_link_probe(Cpp::JitCall* JC) {
  JC->Invoke();
  JC->InvokeConstructor(nullptr);
  JC->InvokeDestructor(nullptr);
}

// ODR-uses the Error.h inline surface. Result<void>::share, CapturedError
// and the ErrorRef / DiagnosticRef forwarders must resolve to dispatch
// slots only. An out-of-line library symbol left behind any of them is
// an UND reference that dlopen(RTLD_NOW) of this lib cannot satisfy.
void downstream_error_probe(Cpp::Result<void>* R) {
  Cpp::CapturedError C = R->share();
  for (Cpp::DiagnosticRef D : Cpp::GetDiagnostics(C.ref()))
    (void)D.message();
  (void)C.record();
}

int downstream_verify_trace_slots(const char* libpath) {
  if (!Cpp::LoadDispatchAPI(libpath))
    return 1;
  if (!CppInternal::DispatchRaw::CppInterOpTraceJitCallInvokeImpl)
    return 2;
  if (!CppInternal::DispatchRaw::CppInterOpTraceJitCallInvokeDestructorImpl)
    return 3;
  if (!CppInternal::DispatchRaw::CppInterOpTraceJitCallInvokeReturnImpl)
    return 4;
  return 0;
}
