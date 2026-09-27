#include "TestDownstreamLib.h"

#include "CppInterOp/Dispatch.h"

#ifndef _WIN32
#include <dlfcn.h>
#endif

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

int downstream_verify_no_self_interposition(const char* libpath) {
#ifdef _WIN32
  // Windows DLLs export through dllexport, so a consumer's inline wrapper does
  // not weakly interpose the real symbol. The bug cannot occur there.
  (void)libpath;
  return 0;
#else
  // Force this DSO to emit an out-of-line copy of the wrapper. With default
  // visibility that copy is exported weak and, under RTLD_GLOBAL, interposes
  // the real Cpp::CreateInterpreter. Hidden visibility keeps it private.
  auto* const wrapperAddr = &Cpp::CreateInterpreter;
  __asm__ __volatile__("" : : "r"(wrapperAddr) : "memory");

  if (!Cpp::LoadDispatchAPI(libpath))
    return 1;

  Dl_info self{};
  Dl_info slot{};
  if (!dladdr(reinterpret_cast<void*>(&downstream_verify_no_self_interposition),
              &self))
    return 3;
  if (!dladdr(
          reinterpret_cast<void*>(CppInternal::DispatchRaw::CreateInterpreter),
          &slot))
    return 4;
  // The dispatch table must bind CreateInterpreter to the CppInterOp library,
  // not back into this consumer DSO.
  return (self.dli_fbase == slot.dli_fbase) ? 2 : 0;
#endif
}
