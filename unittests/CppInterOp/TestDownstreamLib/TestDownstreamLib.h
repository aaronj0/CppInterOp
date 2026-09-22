#ifndef UNITTESTS_CPPINTEROP_TESTDOWNSTREAMLIB_TESTDOWNSTREAMLIB_H
#define UNITTESTS_CPPINTEROP_TESTDOWNSTREAMLIB_TESTDOWNSTREAMLIB_H

// Probe entry that ODR-uses the inline JitCall fast path. JC is opaque
// so the optimizer can't DCE the inlined references at any -O level.
namespace Cpp {
class JitCall;
template <typename T> class Result;
} // namespace Cpp
#ifdef _WIN32
#define TESTDOWNSTREAM_EXPORT extern "C" __declspec(dllexport)
#else
#define TESTDOWNSTREAM_EXPORT extern "C" __attribute__((visibility("default")))
#endif
TESTDOWNSTREAM_EXPORT void downstream_link_probe(Cpp::JitCall* JC);

/// Probe entry that ODR-uses the Error.h inline surface: Result<void>,
/// CapturedError and the ErrorRef / DiagnosticRef member forwarders. R
/// is opaque for the same reason JC is above.
TESTDOWNSTREAM_EXPORT void downstream_error_probe(Cpp::Result<void>* R);

/// After LoadDispatchAPI(libpath) succeeds, check every DispatchRaw
/// trace slot in this DSO is non-null. Returns 0 on success, a
/// positive non-zero code on the first failure (1=LoadDispatchAPI
/// failed, 2/3/4=corresponding slot still null).
TESTDOWNSTREAM_EXPORT int downstream_verify_trace_slots(const char* libpath);

#endif // UNITTESTS_CPPINTEROP_TESTDOWNSTREAMLIB_TESTDOWNSTREAMLIB_H
