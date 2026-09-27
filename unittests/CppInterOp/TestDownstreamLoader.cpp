// dlopens TestDownstreamLib without linking libclangCppInterOp; with
// argv[1] = libclangCppInterOp path, also drives the probe's
// LoadDispatchAPI check to pin the X-macro slot-population contract.

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
using HandleTy = HMODULE;
static HandleTy openLib(const char* p) { return LoadLibraryA(p); }
static HandleTy openLibGlobal(const char* p) { return LoadLibraryA(p); }
static void* findSym(HandleTy h, const char* n) {
  return reinterpret_cast<void*>(GetProcAddress(h, n));
}
static void closeLib(HandleTy h) { FreeLibrary(h); }
static const char* lastErr() { return "LoadLibrary failed"; }
#else
#include <dlfcn.h>
using HandleTy = void*;
static HandleTy openLib(const char* p) {
  return dlopen(p, RTLD_NOW | RTLD_LOCAL);
}
// The global-scope open is what makes a downstream consumer's inline Cpp::
// wrappers able to interpose the real symbols (the CreateInterpreter recursion).
static HandleTy openLibGlobal(const char* p) {
  return dlopen(p, RTLD_NOW | RTLD_GLOBAL);
}
static void* findSym(HandleTy h, const char* n) { return dlsym(h, n); }
static void closeLib(HandleTy h) { dlclose(h); }
static const char* lastErr() { return dlerror(); }
#endif

#ifndef TEST_DOWNSTREAM_LIB_PATH
#error "TEST_DOWNSTREAM_LIB_PATH must be defined"
#endif

int main(int argc, char** argv) {
  // argv[1] is the libclangCppInterOp path. With argv[2] == "global" the
  // downstream lib is opened RTLD_GLOBAL and checked for self-interposition of
  // the dispatch table; otherwise it is opened RTLD_LOCAL and its trace slots
  // are verified.
  const bool global = (argc > 2 && std::strcmp(argv[2], "global") == 0);
  HandleTy h = global ? openLibGlobal(TEST_DOWNSTREAM_LIB_PATH)
                      : openLib(TEST_DOWNSTREAM_LIB_PATH);
  if (!h) {
    std::fprintf(stderr, "open(%s) failed: %s\n", TEST_DOWNSTREAM_LIB_PATH,
                 lastErr());
    return 1;
  }
  int rc = 0;
  if (global) {
    auto* verify = reinterpret_cast<int (*)(const char*)>(
        findSym(h, "downstream_verify_no_self_interposition"));
    if (!verify) {
      std::fprintf(stderr, "missing downstream_verify_no_self_interposition: %s\n",
                   lastErr());
      rc = 2;
    } else {
      rc = verify(argv[1]);
      if (rc != 0)
        std::fprintf(stderr, "downstream_verify_no_self_interposition -> %d\n",
                     rc);
    }
  } else if (argc > 1) {
    auto* verify = reinterpret_cast<int (*)(const char*)>(
        findSym(h, "downstream_verify_trace_slots"));
    if (!verify) {
      std::fprintf(stderr, "missing downstream_verify_trace_slots: %s\n",
                   lastErr());
      rc = 2;
    } else {
      rc = verify(argv[1]);
      if (rc != 0)
        std::fprintf(stderr, "downstream_verify_trace_slots -> %d\n", rc);
    }
  }
  closeLib(h);
  return rc;
}
