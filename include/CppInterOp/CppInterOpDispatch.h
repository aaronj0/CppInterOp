#include "clang-c/ExternC.h"
#include "clang-c/Platform.h"
// CppInterOpDispatch.h
#pragma once

#include <stddef.h>
#include <string.h>
#include <unordered_map>
#include <CppInterOp/CppInterOp.h>

LLVM_CLANG_C_EXTERN_C_BEGIN

typedef void (*__CPP_FUNC)(void);

struct name_address_pair {
   const char *name;
   __CPP_FUNC address;
};

// returns a pointer to the function with the given name, or nullptr if not found.
CINDEX_LINKAGE void (*CppGetProcAddress(const unsigned char *procname))(void);

LLVM_CLANG_C_EXTERN_C_END

namespace CppDispatch {
    // Forward all type aliases
    using TCppIndex_t = ::Cpp::TCppIndex_t;
    using TCppScope_t = ::Cpp::TCppScope_t;
    using TCppConstScope_t = ::Cpp::TCppConstScope_t;
    using TCppType_t = ::Cpp::TCppType_t;
    using TCppFunction_t = ::Cpp::TCppFunction_t;
    using TCppConstFunction_t = ::Cpp::TCppConstFunction_t;
    using TCppFuncAddr_t = ::Cpp::TCppFuncAddr_t;
    using TInterp_t = ::Cpp::TInterp_t;
    using TCppObject_t = ::Cpp::TCppObject_t;
    
    // Forward declare enums
    using Operator = ::Cpp::Operator;
    using OperatorArity = ::Cpp::OperatorArity;
    using QualKind = ::Cpp::QualKind;

    using TemplateArgInfo = ::Cpp::TemplateArgInfo;
    
    // Forward declare the class
    using JitCall = ::Cpp::JitCall;

    
}


// #ifndef CPPINTEROP_DISPATCH_H
// #define CPPINTEROP_DISPATCH_H

// #include <dlfcn.h>
// #include <mutex>
// #include <iostream>
// #include "cppinterop_funcptr_typedefs.h"

// // Forward declarations
// static inline void* dlGetProcAddress(const char* name)
// {
//     if (!name) return nullptr;
    
//     static std::once_flag loaded;
//     static void* handle = nullptr;
//     static void* (*getCppProcAddress)(const char*) = nullptr;
//     static bool initialization_successful = false;
    
//     // Initialize the library once
//     std::call_once(loaded, []() {
//         const char* libPath = "/home/ajomy/cppyy-interop-dev/CppInterOp/build/lib/libclangCppInterOp.so";
//         handle = dlopen(libPath, RTLD_LOCAL | RTLD_NOW);
//         if (!handle) {
//             std::cout << "Failed to open library: " << dlerror() << std::endl;
//             return;
//         }
        
//         getCppProcAddress = reinterpret_cast<void*(*)(const char*)>(dlsym(handle, "CppGetProcAddress"));
//         if (!getCppProcAddress) {
//             std::cout << "Failed to find CppGetProcAddress: " << dlerror() << std::endl;
//             dlclose(handle);
//             handle = nullptr;
//             return;
//         }
        
//         initialization_successful = true;
//     });
//     if (!initialization_successful || !getCppProcAddress) {
//         return nullptr;
//     }
//     return getCppProcAddress(name);
// }

// #define EXTERN_CPP_FUNC(func_name) \
//     extern CppAPIType::func_name func_name;


// #define LOAD_CPP_FUNCTION(func_name) \
//     func_name = reinterpret_cast<CppAPIType::func_name>(dlGetProcAddress(#func_name));

// namespace CppDispatch {
// EXTERN_CPP_FUNC(CreateInterpreter);
// EXTERN_CPP_FUNC(GetInterpreter);
// EXTERN_CPP_FUNC(Process);
// EXTERN_CPP_FUNC(GetResourceDir);
// EXTERN_CPP_FUNC(AddIncludePath);
// EXTERN_CPP_FUNC(LoadLibrary);
// EXTERN_CPP_FUNC(Declare);
// EXTERN_CPP_FUNC(DeleteInterpreter);
// EXTERN_CPP_FUNC(IsNamespace);
// EXTERN_CPP_FUNC(ObjToString);
// EXTERN_CPP_FUNC(GetQualifiedCompleteName);
// EXTERN_CPP_FUNC(IsLValueReferenceType);
// EXTERN_CPP_FUNC(GetNonReferenceType);
// EXTERN_CPP_FUNC(IsEnumType);
// EXTERN_CPP_FUNC(GetIntegerTypeFromEnumType);
// EXTERN_CPP_FUNC(GetReferencedType);
// EXTERN_CPP_FUNC(IsPointerType);
// EXTERN_CPP_FUNC(GetPointeeType);
// EXTERN_CPP_FUNC(GetPointerType);
// EXTERN_CPP_FUNC(IsReferenceType);
// EXTERN_CPP_FUNC(GetTypeAsString);
// EXTERN_CPP_FUNC(GetCanonicalType);
// EXTERN_CPP_FUNC(HasTypeQualifier);
// EXTERN_CPP_FUNC(RemoveTypeQualifier);
// EXTERN_CPP_FUNC(GetUnderlyingType);
// EXTERN_CPP_FUNC(IsRecordType);
// EXTERN_CPP_FUNC(IsFunctionPointerType);
// EXTERN_CPP_FUNC(GetVariableType);
// EXTERN_CPP_FUNC(GetNamed);
// EXTERN_CPP_FUNC(GetScopeFromType);
// EXTERN_CPP_FUNC(GetClassTemplateInstantiationArgs);
// EXTERN_CPP_FUNC(IsClass);
// EXTERN_CPP_FUNC(GetType);
// EXTERN_CPP_FUNC(GetTypeFromScope);
// EXTERN_CPP_FUNC(GetComplexType);
// EXTERN_CPP_FUNC(GetIntegerTypeFromEnumScope);
// EXTERN_CPP_FUNC(GetUnderlyingScope);
// EXTERN_CPP_FUNC(GetScope);
// EXTERN_CPP_FUNC(GetGlobalScope);
// EXTERN_CPP_FUNC(GetScopeFromCompleteName);
// EXTERN_CPP_FUNC(InstantiateTemplate);
// EXTERN_CPP_FUNC(GetParentScope);
// EXTERN_CPP_FUNC(IsTemplate);
// EXTERN_CPP_FUNC(IsTemplateSpecialization);
// EXTERN_CPP_FUNC(IsTypedefed);
// EXTERN_CPP_FUNC(IsClassPolymorphic);
// EXTERN_CPP_FUNC(Demangle);
// EXTERN_CPP_FUNC(SizeOf);
// EXTERN_CPP_FUNC(GetSizeOfType);
// EXTERN_CPP_FUNC(IsBuiltin);
// EXTERN_CPP_FUNC(IsComplete);
// EXTERN_CPP_FUNC(Allocate);
// EXTERN_CPP_FUNC(Deallocate);
// EXTERN_CPP_FUNC(Construct);
// EXTERN_CPP_FUNC(Destruct);
// EXTERN_CPP_FUNC(MakeFunctionCallable);
// EXTERN_CPP_FUNC(GetFunctionAddress);
// EXTERN_CPP_FUNC(IsAbstract);
// EXTERN_CPP_FUNC(IsEnumScope);
// EXTERN_CPP_FUNC(IsEnumConstant);
// EXTERN_CPP_FUNC(IsAggregate);
// EXTERN_CPP_FUNC(HasDefaultConstructor);
// EXTERN_CPP_FUNC(IsVariable);
// EXTERN_CPP_FUNC(GetAllCppNames);
// EXTERN_CPP_FUNC(GetUsingNamespaces);
// EXTERN_CPP_FUNC(GetCompleteName);
// EXTERN_CPP_FUNC(GetDestructor);
// EXTERN_CPP_FUNC(IsVirtualMethod);
// EXTERN_CPP_FUNC(GetNumBases);
// EXTERN_CPP_FUNC(GetName);
// EXTERN_CPP_FUNC(GetBaseClass);
// EXTERN_CPP_FUNC(IsSubclass);
// EXTERN_CPP_FUNC(GetOperator);
// EXTERN_CPP_FUNC(GetFunctionReturnType);
// EXTERN_CPP_FUNC(GetBaseClassOffset);
// EXTERN_CPP_FUNC(GetClassMethods);
// EXTERN_CPP_FUNC(GetFunctionsUsingName);
// EXTERN_CPP_FUNC(GetFunctionNumArgs);
// EXTERN_CPP_FUNC(GetFunctionRequiredArgs);
// EXTERN_CPP_FUNC(GetFunctionArgName);
// EXTERN_CPP_FUNC(GetFunctionArgType);
// EXTERN_CPP_FUNC(GetFunctionArgDefault);
// EXTERN_CPP_FUNC(GetFunctionPrototype);
// EXTERN_CPP_FUNC(IsConstMethod);
// EXTERN_CPP_FUNC(GetFunctionTemplatedDecls);
// EXTERN_CPP_FUNC(ExistsFunctionTemplate);
// EXTERN_CPP_FUNC(IsTemplatedFunction);
// EXTERN_CPP_FUNC(IsStaticMethod);
// EXTERN_CPP_FUNC(GetClassTemplatedMethods);
// EXTERN_CPP_FUNC(BestOverloadFunctionMatch);
// EXTERN_CPP_FUNC(GetOperatorFromSpelling);
// EXTERN_CPP_FUNC(IsFunctionDeleted);
// EXTERN_CPP_FUNC(IsPublicMethod);
// EXTERN_CPP_FUNC(IsProtectedMethod);
// EXTERN_CPP_FUNC(IsPrivateMethod);
// EXTERN_CPP_FUNC(IsConstructor);
// EXTERN_CPP_FUNC(IsDestructor);
// EXTERN_CPP_FUNC(GetDatamembers);
// EXTERN_CPP_FUNC(GetStaticDatamembers);
// EXTERN_CPP_FUNC(GetEnumConstantDatamembers);
// EXTERN_CPP_FUNC(LookupDatamember);
// EXTERN_CPP_FUNC(IsLambdaClass);
// EXTERN_CPP_FUNC(GetQualifiedName);
// EXTERN_CPP_FUNC(GetVariableOffset);
// EXTERN_CPP_FUNC(IsPublicVariable);
// EXTERN_CPP_FUNC(IsProtectedVariable);
// EXTERN_CPP_FUNC(IsPrivateVariable);
// EXTERN_CPP_FUNC(IsStaticVariable);
// EXTERN_CPP_FUNC(IsConstVariable);
// EXTERN_CPP_FUNC(GetDimensions);
// EXTERN_CPP_FUNC(GetEnumConstants);
// EXTERN_CPP_FUNC(GetEnumConstantType);
// EXTERN_CPP_FUNC(GetEnumConstantValue);
// EXTERN_CPP_FUNC(DumpScope);
// EXTERN_CPP_FUNC(AddSearchPath);
// EXTERN_CPP_FUNC(Evaluate);
// EXTERN_CPP_FUNC(IsDebugOutputEnabled);
// EXTERN_CPP_FUNC(EnableDebugOutput);

// static inline int init_functions() {
//     LOAD_CPP_FUNCTION(CreateInterpreter);
//     LOAD_CPP_FUNCTION(GetInterpreter);
//     LOAD_CPP_FUNCTION(Process);
//     LOAD_CPP_FUNCTION(GetResourceDir);
//     LOAD_CPP_FUNCTION(AddIncludePath);
//     LOAD_CPP_FUNCTION(LoadLibrary);
//     LOAD_CPP_FUNCTION(Declare);
//     LOAD_CPP_FUNCTION(DeleteInterpreter);
//     LOAD_CPP_FUNCTION(IsNamespace);
//     LOAD_CPP_FUNCTION(ObjToString);
//     LOAD_CPP_FUNCTION(GetQualifiedCompleteName);
//     LOAD_CPP_FUNCTION(IsLValueReferenceType);
//     LOAD_CPP_FUNCTION(GetNonReferenceType);
//     LOAD_CPP_FUNCTION(IsEnumType);
//     LOAD_CPP_FUNCTION(GetIntegerTypeFromEnumType);
//     LOAD_CPP_FUNCTION(GetReferencedType);
//     LOAD_CPP_FUNCTION(IsPointerType);
//     LOAD_CPP_FUNCTION(GetPointeeType);
//     LOAD_CPP_FUNCTION(GetPointerType);
//     LOAD_CPP_FUNCTION(IsReferenceType);
//     LOAD_CPP_FUNCTION(GetTypeAsString);
//     LOAD_CPP_FUNCTION(GetCanonicalType);
//     LOAD_CPP_FUNCTION(HasTypeQualifier);
//     LOAD_CPP_FUNCTION(RemoveTypeQualifier);
//     LOAD_CPP_FUNCTION(GetUnderlyingType);
//     LOAD_CPP_FUNCTION(IsRecordType);
//     LOAD_CPP_FUNCTION(IsFunctionPointerType);
//     LOAD_CPP_FUNCTION(GetVariableType);
//     LOAD_CPP_FUNCTION(GetNamed);
//     LOAD_CPP_FUNCTION(GetScopeFromType);
//     LOAD_CPP_FUNCTION(GetClassTemplateInstantiationArgs);
//     LOAD_CPP_FUNCTION(IsClass);
//     LOAD_CPP_FUNCTION(GetType);
//     LOAD_CPP_FUNCTION(GetTypeFromScope);
//     LOAD_CPP_FUNCTION(GetComplexType);
//     LOAD_CPP_FUNCTION(GetIntegerTypeFromEnumScope);
//     LOAD_CPP_FUNCTION(GetUnderlyingScope);
//     LOAD_CPP_FUNCTION(GetScope);
//     LOAD_CPP_FUNCTION(GetGlobalScope);
//     LOAD_CPP_FUNCTION(GetScopeFromCompleteName);
//     LOAD_CPP_FUNCTION(InstantiateTemplate);
//     LOAD_CPP_FUNCTION(GetParentScope);
//     LOAD_CPP_FUNCTION(IsTemplate);
//     LOAD_CPP_FUNCTION(IsTemplateSpecialization);
//     LOAD_CPP_FUNCTION(IsTypedefed);
//     LOAD_CPP_FUNCTION(IsClassPolymorphic);
//     LOAD_CPP_FUNCTION(Demangle);
//     LOAD_CPP_FUNCTION(SizeOf);
//     LOAD_CPP_FUNCTION(GetSizeOfType);
//     LOAD_CPP_FUNCTION(IsBuiltin);
//     LOAD_CPP_FUNCTION(IsComplete);
//     LOAD_CPP_FUNCTION(Allocate);
//     LOAD_CPP_FUNCTION(Deallocate);
//     LOAD_CPP_FUNCTION(Construct);
//     LOAD_CPP_FUNCTION(Destruct);
//     LOAD_CPP_FUNCTION(MakeFunctionCallable);
//     LOAD_CPP_FUNCTION(GetFunctionAddress);
//     LOAD_CPP_FUNCTION(IsAbstract);
//     LOAD_CPP_FUNCTION(IsEnumScope);
//     LOAD_CPP_FUNCTION(IsEnumConstant);
//     LOAD_CPP_FUNCTION(IsAggregate);
//     LOAD_CPP_FUNCTION(HasDefaultConstructor);
//     LOAD_CPP_FUNCTION(IsVariable);
//     LOAD_CPP_FUNCTION(GetAllCppNames);
//     LOAD_CPP_FUNCTION(GetUsingNamespaces);
//     LOAD_CPP_FUNCTION(GetCompleteName);
//     LOAD_CPP_FUNCTION(GetDestructor);
//     LOAD_CPP_FUNCTION(IsVirtualMethod);
//     LOAD_CPP_FUNCTION(GetNumBases);
//     LOAD_CPP_FUNCTION(GetName);
//     LOAD_CPP_FUNCTION(GetBaseClass);
//     LOAD_CPP_FUNCTION(IsSubclass);
//     LOAD_CPP_FUNCTION(GetOperator);
//     LOAD_CPP_FUNCTION(GetFunctionReturnType);
//     LOAD_CPP_FUNCTION(GetBaseClassOffset);
//     LOAD_CPP_FUNCTION(GetClassMethods);
//     LOAD_CPP_FUNCTION(GetFunctionsUsingName);
//     LOAD_CPP_FUNCTION(GetFunctionNumArgs);
//     LOAD_CPP_FUNCTION(GetFunctionRequiredArgs);
//     LOAD_CPP_FUNCTION(GetFunctionArgName);
//     LOAD_CPP_FUNCTION(GetFunctionArgType);
//     LOAD_CPP_FUNCTION(GetFunctionArgDefault);
//     LOAD_CPP_FUNCTION(GetFunctionPrototype);
//     LOAD_CPP_FUNCTION(IsConstMethod);
//     LOAD_CPP_FUNCTION(GetFunctionTemplatedDecls);
//     LOAD_CPP_FUNCTION(ExistsFunctionTemplate);
//     LOAD_CPP_FUNCTION(IsTemplatedFunction);
//     LOAD_CPP_FUNCTION(IsStaticMethod);
//     LOAD_CPP_FUNCTION(GetClassTemplatedMethods);
//     LOAD_CPP_FUNCTION(BestOverloadFunctionMatch);
//     LOAD_CPP_FUNCTION(GetOperatorFromSpelling);
//     LOAD_CPP_FUNCTION(IsFunctionDeleted);
//     LOAD_CPP_FUNCTION(IsPublicMethod);
//     LOAD_CPP_FUNCTION(IsProtectedMethod);
//     LOAD_CPP_FUNCTION(IsPrivateMethod);
//     LOAD_CPP_FUNCTION(IsConstructor);
//     LOAD_CPP_FUNCTION(IsDestructor);
//     LOAD_CPP_FUNCTION(GetDatamembers);
//     LOAD_CPP_FUNCTION(GetStaticDatamembers);
//     LOAD_CPP_FUNCTION(GetEnumConstantDatamembers);
//     LOAD_CPP_FUNCTION(LookupDatamember);
//     LOAD_CPP_FUNCTION(IsLambdaClass);
//     LOAD_CPP_FUNCTION(GetQualifiedName);
//     LOAD_CPP_FUNCTION(GetVariableOffset);
//     LOAD_CPP_FUNCTION(IsPublicVariable);
//     LOAD_CPP_FUNCTION(IsProtectedVariable);
//     LOAD_CPP_FUNCTION(IsPrivateVariable);
//     LOAD_CPP_FUNCTION(IsStaticVariable);
//     LOAD_CPP_FUNCTION(IsConstVariable);
//     LOAD_CPP_FUNCTION(GetDimensions);
//     LOAD_CPP_FUNCTION(GetEnumConstants);
//     LOAD_CPP_FUNCTION(GetEnumConstantType);
//     LOAD_CPP_FUNCTION(GetEnumConstantValue);
//     LOAD_CPP_FUNCTION(DumpScope);
//     LOAD_CPP_FUNCTION(AddSearchPath);
//     LOAD_CPP_FUNCTION(Evaluate);
//     LOAD_CPP_FUNCTION(IsDebugOutputEnabled);
//     LOAD_CPP_FUNCTION(EnableDebugOutput);
//     // print the address of the AddSearchPath function
//     std::cout<<"AddSearchPath function address: " << reinterpret_cast<void*>(AddSearchPath) << std::endl;
//     std::cout<<"LoadLibrary function address: " << reinterpret_cast<void*>(LoadLibrary) << std::endl;
//     std::cout<<"Ebable function address: " << reinterpret_cast<void*>(EnableDebugOutput) << std::endl;
//     return 0;
// }
// }
// #endif // CPPINTEROP_DISPATCH_H
