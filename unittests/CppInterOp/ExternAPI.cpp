#include "Utils.h"

#include "CppInterOp/CppInterOp.h"

#include "clang/AST/ASTContext.h"
#include "clang/Basic/Version.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"

#include "gtest/gtest.h"
#include <dlfcn.h>
#include <string>

using namespace TestUtils;
using namespace llvm;
using namespace clang;


// TEST(ExternAPITest, FindGetVersion) {

// void* cppinterop_handle = dlopen("libclangCppInterOp.so", RTLD_LOCAL);
// if (!cppinterop_handle) { /* handle error */ }

// using GetVersionFunc = std::string (*)();
// GetVersionFunc GetVersion = (GetVersionFunc)dlsym(cppinterop_handle, "Cpp::GetVersion");
// if (!GetVersion) { /* handle error */ }

// }

TEST(ExternAPITest, GetVersionSymbolLookup) {
  const char* libPath = "/home/ajomy/cppyy-interop-dev/CppInterOp/build/lib/libclangCppInterOp.so";
  void* handle = dlopen(libPath, RTLD_LOCAL | RTLD_NOW);
  ASSERT_NE(handle, nullptr) << "Failed to open library: " << dlerror();

  typedef const char* (*GetVersionFn)();
  GetVersionFn get_version = (GetVersionFn)dlsym(handle, "cppinterop_get_version_c");
  ASSERT_NE(get_version, nullptr) << "failed to locate symbol: " << dlerror();
  const char* version_cstr = get_version();
  ASSERT_NE(version_cstr, nullptr) << "string is null";
  std::string version(version_cstr);
  std::cout<<"\nHELLO\n"<<version<<"\n";

  dlclose(handle);
}
