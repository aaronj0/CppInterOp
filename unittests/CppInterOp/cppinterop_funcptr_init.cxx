#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include "cppinterop_funcptr_declarations.h"

bool initCppInterOpFuncPtrs(const char* libname = "libclangCppInterOp.so") {
    void* handle = dlopen(libname, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Failed to open %s: %s\n", libname, dlerror());
        return false;
    }
    dlerror();

    using namespace Cpp;
    pGetVersion = (decltype(pGetVersion))dlsym(handle, "pGetVersion");
    if (!pGetVersion) { fprintf(stderr, "Failed to load pGetVersion: %s\n", dlerror()); return false; }
    pDemangle = (decltype(pDemangle))dlsym(handle, "pDemangle");
    if (!pDemangle) { fprintf(stderr, "Failed to load pDemangle: %s\n", dlerror()); return false; }
    pEnableDebugOutput = (decltype(pEnableDebugOutput))dlsym(handle, "pEnableDebugOutput");
    if (!pEnableDebugOutput) { fprintf(stderr, "Failed to load pEnableDebugOutput: %s\n", dlerror()); return false; }
    pIsDebugOutputEnabled = (decltype(pIsDebugOutputEnabled))dlsym(handle, "pIsDebugOutputEnabled");
    if (!pIsDebugOutputEnabled) { fprintf(stderr, "Failed to load pIsDebugOutputEnabled: %s\n", dlerror()); return false; }
    pIsAggregate = (decltype(pIsAggregate))dlsym(handle, "pIsAggregate");
    if (!pIsAggregate) { fprintf(stderr, "Failed to load pIsAggregate: %s\n", dlerror()); return false; }
    pIsNamespace = (decltype(pIsNamespace))dlsym(handle, "pIsNamespace");
    if (!pIsNamespace) { fprintf(stderr, "Failed to load pIsNamespace: %s\n", dlerror()); return false; }
    pIsClass = (decltype(pIsClass))dlsym(handle, "pIsClass");
    if (!pIsClass) { fprintf(stderr, "Failed to load pIsClass: %s\n", dlerror()); return false; }
    pIsFunction = (decltype(pIsFunction))dlsym(handle, "pIsFunction");
    if (!pIsFunction) { fprintf(stderr, "Failed to load pIsFunction: %s\n", dlerror()); return false; }
    pIsFunctionPointerType = (decltype(pIsFunctionPointerType))dlsym(handle, "pIsFunctionPointerType");
    if (!pIsFunctionPointerType) { fprintf(stderr, "Failed to load pIsFunctionPointerType: %s\n", dlerror()); return false; }
    pIsClassPolymorphic = (decltype(pIsClassPolymorphic))dlsym(handle, "pIsClassPolymorphic");
    if (!pIsClassPolymorphic) { fprintf(stderr, "Failed to load pIsClassPolymorphic: %s\n", dlerror()); return false; }
    pIsComplete = (decltype(pIsComplete))dlsym(handle, "pIsComplete");
    if (!pIsComplete) { fprintf(stderr, "Failed to load pIsComplete: %s\n", dlerror()); return false; }
    pSizeOf = (decltype(pSizeOf))dlsym(handle, "pSizeOf");
    if (!pSizeOf) { fprintf(stderr, "Failed to load pSizeOf: %s\n", dlerror()); return false; }
    pIsBuiltin = (decltype(pIsBuiltin))dlsym(handle, "pIsBuiltin");
    if (!pIsBuiltin) { fprintf(stderr, "Failed to load pIsBuiltin: %s\n", dlerror()); return false; }
    pIsTemplate = (decltype(pIsTemplate))dlsym(handle, "pIsTemplate");
    if (!pIsTemplate) { fprintf(stderr, "Failed to load pIsTemplate: %s\n", dlerror()); return false; }
    pIsTemplateSpecialization = (decltype(pIsTemplateSpecialization))dlsym(handle, "pIsTemplateSpecialization");
    if (!pIsTemplateSpecialization) { fprintf(stderr, "Failed to load pIsTemplateSpecialization: %s\n", dlerror()); return false; }
    pIsTypedefed = (decltype(pIsTypedefed))dlsym(handle, "pIsTypedefed");
    if (!pIsTypedefed) { fprintf(stderr, "Failed to load pIsTypedefed: %s\n", dlerror()); return false; }
    pIsAbstract = (decltype(pIsAbstract))dlsym(handle, "pIsAbstract");
    if (!pIsAbstract) { fprintf(stderr, "Failed to load pIsAbstract: %s\n", dlerror()); return false; }
    pIsEnumScope = (decltype(pIsEnumScope))dlsym(handle, "pIsEnumScope");
    if (!pIsEnumScope) { fprintf(stderr, "Failed to load pIsEnumScope: %s\n", dlerror()); return false; }
    pIsEnumConstant = (decltype(pIsEnumConstant))dlsym(handle, "pIsEnumConstant");
    if (!pIsEnumConstant) { fprintf(stderr, "Failed to load pIsEnumConstant: %s\n", dlerror()); return false; }
    pIsEnumType = (decltype(pIsEnumType))dlsym(handle, "pIsEnumType");
    if (!pIsEnumType) { fprintf(stderr, "Failed to load pIsEnumType: %s\n", dlerror()); return false; }
    pHasTypeQualifier = (decltype(pHasTypeQualifier))dlsym(handle, "pHasTypeQualifier");
    if (!pHasTypeQualifier) { fprintf(stderr, "Failed to load pHasTypeQualifier: %s\n", dlerror()); return false; }
    pRemoveTypeQualifier = (decltype(pRemoveTypeQualifier))dlsym(handle, "pRemoveTypeQualifier");
    if (!pRemoveTypeQualifier) { fprintf(stderr, "Failed to load pRemoveTypeQualifier: %s\n", dlerror()); return false; }
    pAddTypeQualifier = (decltype(pAddTypeQualifier))dlsym(handle, "pAddTypeQualifier");
    if (!pAddTypeQualifier) { fprintf(stderr, "Failed to load pAddTypeQualifier: %s\n", dlerror()); return false; }
    pGetEnums = (decltype(pGetEnums))dlsym(handle, "pGetEnums");
    if (!pGetEnums) { fprintf(stderr, "Failed to load pGetEnums: %s\n", dlerror()); return false; }
    pIsSmartPtrType = (decltype(pIsSmartPtrType))dlsym(handle, "pIsSmartPtrType");
    if (!pIsSmartPtrType) { fprintf(stderr, "Failed to load pIsSmartPtrType: %s\n", dlerror()); return false; }
    // ... 
    return true;
}


// Approach 2:

#include "cppinterop_funcptr_typedefs.h"
#include "cppinterop_funcptr_declarations.h"

#include <dlfcn.h>
#include <cstdio>

namespace Cpp {

static void* sLibHandle = nullptr;

// expose specific symbol
#define LOAD_SYMBOL(sym)                                  \
    do {                                                 \
        p##sym = (decltype(p##sym))dlsym(sLibHandle, #sym); \
        if (!p##sym) {                                   \
            fprintf(stderr, "Failed to load symbol: %s\n", #sym); \
            success = false;                             \
        }                                                \
    } while (0)

bool InitFunctionPointers() {
    if (sLibHandle)
        return true;

    sLibHandle = dlopen("libclangCppInterOp.so", RTLD_LAZY | RTLD_LOCAL);
    if (!sLibHandle) {
        fprintf(stderr, "failed to open libclangCppInterOp.so: %s\n", dlerror());
        return false;
    }

    bool success = true;

    // load all func ptrs declared in cppinterop_funcptr_declarations.h
    LOAD_SYMBOL(GetVersion);
    LOAD_SYMBOL(Demangle);
    LOAD_SYMBOL(EnableDebugOutput);
    LOAD_SYMBOL(IsDebugOutputEnabled);
    LOAD_SYMBOL(IsAggregate);
    LOAD_SYMBOL(IsNamespace);
    LOAD_SYMBOL(IsClass);
    LOAD_SYMBOL(IsFunction);
    LOAD_SYMBOL(IsFunctionPointerType);
    LOAD_SYMBOL(IsClassPolymorphic);
    LOAD_SYMBOL(IsComplete);
    LOAD_SYMBOL(SizeOf);
    LOAD_SYMBOL(IsBuiltin);
    LOAD_SYMBOL(IsTemplate);
    LOAD_SYMBOL(IsTemplateSpecialization);
    LOAD_SYMBOL(IsTypedefed);
    LOAD_SYMBOL(IsAbstract);
    LOAD_SYMBOL(IsEnumScope);
    LOAD_SYMBOL(IsEnumConstant);
    LOAD_SYMBOL(IsEnumType);
    LOAD_SYMBOL(HasTypeQualifier);
    LOAD_SYMBOL(RemoveTypeQualifier);
    LOAD_SYMBOL(AddTypeQualifier);
    LOAD_SYMBOL(GetEnums);
    LOAD_SYMBOL(IsSmartPtrType);
    LOAD_SYMBOL(GetIntegerTypeFromEnumScope);
    LOAD_SYMBOL(GetIntegerTypeFromEnumType);
    LOAD_SYMBOL(GetEnumConstants);
    LOAD_SYMBOL(GetEnumConstantType);
//     LOAD_SYMBOL(GetEnumConstantValue);
//     LOAD_SYMBOL(GetSizeOfType);
//     LOAD_SYMBOL(IsVariable);
//     LOAD_SYMBOL(GetName);
//     LOAD_SYMBOL(GetCompleteName);
//     LOAD_SYMBOL(GetQualifiedName);
//     LOAD_SYMBOL(GetQualifiedCompleteName);
//     LOAD_SYMBOL(GetUsingNamespaces);
//     LOAD_SYMBOL(GetGlobalScope);
//     LOAD_SYMBOL(GetUnderlyingScope);
//     LOAD_SYMBOL(GetScope);
//     LOAD_SYMBOL(GetScopeFromCompleteName);
//     LOAD_SYMBOL(GetNamed);
//     LOAD_SYMBOL(GetParentScope);
//     LOAD_SYMBOL(GetScopeFromType);
//     LOAD_SYMBOL(GetNumBases);
//     LOAD_SYMBOL(GetBaseClass);
//     LOAD_SYMBOL(IsSubclass);
//     LOAD_SYMBOL(GetBaseClassOffset);
//     LOAD_SYMBOL(GetClassMethods);
//     LOAD_SYMBOL(GetFunctionTemplatedDecls);
//     LOAD_SYMBOL(HasDefaultConstructor);
//     LOAD_SYMBOL(GetDefaultConstructor);
//     LOAD_SYMBOL(GetDestructor);
//     LOAD_SYMBOL(GetFunctionsUsingName);
//     LOAD_SYMBOL(GetFunctionReturnType);
//     LOAD_SYMBOL(GetFunctionNumArgs);
//     LOAD_SYMBOL(GetFunctionRequiredArgs);
//     LOAD_SYMBOL(GetFunctionArgType);
//     LOAD_SYMBOL(GetFunctionSignature);
//     LOAD_SYMBOL(IsFunctionDeleted);
//     LOAD_SYMBOL(IsTemplatedFunction);
//     LOAD_SYMBOL(ExistsFunctionTemplate);
//     LOAD_SYMBOL(GetClassTemplatedMethods);
//     LOAD_SYMBOL(IsMethod);
//     LOAD_SYMBOL(IsPublicMethod);
//     LOAD_SYMBOL(IsProtectedMethod);
//     LOAD_SYMBOL(IsPrivateMethod);
//     LOAD_SYMBOL(IsConstructor);
//     LOAD_SYMBOL(IsDestructor);
//     LOAD_SYMBOL(IsStaticMethod);
//     LOAD_SYMBOL(GetFunctionAddressFromName);
//     LOAD_SYMBOL(GetFunctionAddressFromMethod);
//     LOAD_SYMBOL(IsVirtualMethod);
//     LOAD_SYMBOL(GetDatamembers);
//     LOAD_SYMBOL(GetStaticDatamembers);
//     LOAD_SYMBOL(GetEnumConstantDatamembers);
//     LOAD_SYMBOL(LookupDatamember);
//     LOAD_SYMBOL(IsLambdaClass);
//     LOAD_SYMBOL(GetVariableType);
//     LOAD_SYMBOL(GetVariableOffset);
//     LOAD_SYMBOL(IsPublicVariable);
//     LOAD_SYMBOL(IsProtectedVariable);
//     LOAD_SYMBOL(IsPrivateVariable);
//     LOAD_SYMBOL(IsStaticVariable);
//     LOAD_SYMBOL(IsConstVariable);
//     LOAD_SYMBOL(IsRecordType);
//     LOAD_SYMBOL(IsPODType);
//     LOAD_SYMBOL(IsPointerType);
//     LOAD_SYMBOL(GetPointeeType);
//     LOAD_SYMBOL(IsReferenceType);
//     LOAD_SYMBOL(IsLValueReferenceType);
//     LOAD_SYMBOL(IsRValueReferenceType);
//     LOAD_SYMBOL(GetPointerType);
//     LOAD_SYMBOL(GetReferencedType);
//     LOAD_SYMBOL(GetNonReferenceType);
//     LOAD_SYMBOL(GetTypeAsString);
//     LOAD_SYMBOL(GetCanonicalType);
//     LOAD_SYMBOL(MakeFunctionCallable);
//     LOAD_SYMBOL(MakeFunctionCallableWithInterp);
//     LOAD_SYMBOL(IsConstMethod);
//     LOAD_SYMBOL(GetFunctionArgDefault);
//     LOAD_SYMBOL(GetFunctionArgName);
//     LOAD_SYMBOL(GetSpellingFromOperator);
//     LOAD_SYMBOL(GetOperatorFromSpelling);
//     LOAD_SYMBOL(GetOperatorArity);
//     LOAD_SYMBOL(GetOperator);
//     LOAD_SYMBOL(CreateInterpreter);
//     LOAD_SYMBOL(DeleteInterpreter);
//     LOAD_SYMBOL(ActivateInterpreter);
//     LOAD_SYMBOL(GetInterpreter);
//     LOAD_SYMBOL(UseExternalInterpreter);
//     LOAD_SYMBOL(AddSearchPath);
//     LOAD_SYMBOL(GetResourceDir);
//     LOAD_SYMBOL(DetectResourceDir);
//     LOAD_SYMBOL(DetectSystemCompilerIncludePaths);
//     LOAD_SYMBOL(AddIncludePath);
//     LOAD_SYMBOL(GetIncludePaths);
//     LOAD_SYMBOL(Declare);
//     LOAD_SYMBOL(Process);
//     LOAD_SYMBOL(Evaluate);
//     LOAD_SYMBOL(LookupLibrary);
//     LOAD_SYMBOL(LoadLibrary);
//     LOAD_SYMBOL(UnloadLibrary);
//     LOAD_SYMBOL(SearchLibrariesForSymbol);
//     LOAD_SYMBOL(InsertOrReplaceJitSymbol);

//     return success;
// }

close and reset pointers
void Cleanup() {
    if (sLibHandle) {
        dlclose(sLibHandle);
        sLibHandle = nullptr;


#define RESET_POINTER(sym) p##sym = nullptr;
        RESET_POINTER(GetVersion);
        RESET_POINTER(Demangle);
        RESET_POINTER(EnableDebugOutput);
        RESET_POINTER(IsDebugOutputEnabled);
        RESET_POINTER(IsAggregate);
        RESET_POINTER(IsNamespace);
        RESET_POINTER(IsClass);
        RESET_POINTER(IsFunction);
//         RESET_POINTER(IsFunctionPointerType);
//         RESET_POINTER(IsClassPolymorphic);
//         RESET_POINTER(IsComplete);
//         RESET_POINTER(SizeOf);
//         RESET_POINTER(IsBuiltin);
//         RESET_POINTER(IsTemplate);
//         RESET_POINTER(IsTemplateSpecialization);
//         RESET_POINTER(IsTypedefed);
//         RESET_POINTER(IsAbstract);
//         RESET_POINTER(IsEnumScope);
//         RESET_POINTER(IsEnumConstant);
//         RESET_POINTER(IsEnumType);
//         RESET_POINTER(HasTypeQualifier);
//         RESET_POINTER(RemoveTypeQualifier);
//         RESET_POINTER(AddTypeQualifier);
//         RESET_POINTER(GetEnums);
//         RESET_POINTER(IsSmartPtrType);
//         RESET_POINTER(GetIntegerTypeFromEnumScope);
//         RESET_POINTER(GetIntegerTypeFromEnumType);
//         RESET_POINTER(GetEnumConstants);
//         RESET_POINTER(GetEnumConstantType);
//         RESET_POINTER(GetEnumConstantValue);
//         RESET_POINTER(GetSizeOfType);
//         RESET_POINTER(IsVariable);
//         RESET_POINTER(GetName);
//         RESET_POINTER(GetCompleteName);
//         RESET_POINTER(GetQualifiedName);
//         RESET_POINTER(GetQualifiedCompleteName);
//         RESET_POINTER(GetUsingNamespaces);
//         RESET_POINTER(GetGlobalScope);
//         RESET_POINTER(GetUnderlyingScope);
//         RESET_POINTER(GetScope);
//         RESET_POINTER(GetScopeFromCompleteName);
//         RESET_POINTER(GetNamed);
//         RESET_POINTER(GetParentScope);
//         RESET_POINTER(GetScopeFromType);
//         RESET_POINTER(GetNumBases);
//         RESET_POINTER(GetBaseClass);
//         RESET_POINTER(IsSubclass);
//         RESET_POINTER(GetBaseClassOffset);
//         RESET_POINTER(GetClassMethods);
//         RESET_POINTER(GetFunctionTemplatedDecls);
//         RESET_POINTER(HasDefaultConstructor);
//         RESET_POINTER(GetDefaultConstructor);
//         RESET_POINTER(GetDestructor);
//         RESET_POINTER(GetFunctionsUsingName);
//         RESET_POINTER(GetFunctionReturnType);
//         RESET_POINTER(GetFunctionNumArgs);
//         RESET_POINTER(GetFunctionRequiredArgs);
//         RESET_POINTER(GetFunctionArgType);
//         RESET_POINTER(GetFunctionSignature);
//         RESET_POINTER(IsFunctionDeleted);
//         RESET_POINTER(IsTemplatedFunction);
//         RESET_POINTER(ExistsFunctionTemplate);
//         RESET_POINTER(GetClassTemplatedMethods);
//         RESET_POINTER(IsMethod);
//         RESET_POINTER(IsPublicMethod);
//         RESET_POINTER(IsProtectedMethod);
//         RESET_POINTER(IsPrivateMethod);
//         RESET_POINTER(IsConstructor);
//         RESET_POINTER(IsDestructor);
//         RESET_POINTER(IsStaticMethod);
//         RESET_POINTER(GetFunctionAddressFromName);
//         RESET_POINTER(GetFunctionAddressFromMethod);
//         RESET_POINTER(IsVirtualMethod);
//         RESET_POINTER(GetDatamembers);
//         RESET_POINTER(GetStaticDatamembers);
//         RESET_POINTER(GetEnumConstantDatamembers);
//         RESET_POINTER(LookupDatamember);
//         RESET_POINTER(IsLambdaClass);
//         RESET_POINTER(GetVariableType);
//         RESET_POINTER(GetVariableOffset);
//         RESET_POINTER(IsPublicVariable);
//         RESET_POINTER(IsProtectedVariable);
//         RESET_POINTER(IsPrivateVariable);
//         RESET_POINTER(IsStaticVariable);
//         RESET_POINTER(IsConstVariable);
//         RESET_POINTER(IsRecordType);
//         RESET_POINTER(IsPODType);
//         RESET_POINTER(IsPointerType);
//         RESET_POINTER(GetPointeeType);
//         RESET_POINTER(IsReferenceType);
//         RESET_POINTER(IsLValueReferenceType);
//         RESET_POINTER(IsRValueReferenceType);
//         RESET_POINTER(GetPointerType);
//         RESET_POINTER(GetReferencedType);
//         RESET_POINTER(GetNonReferenceType);
//         RESET_POINTER(GetTypeAsString);
//         RESET_POINTER(GetCanonicalType);
//         RESET_POINTER(MakeFunctionCallable);
//         RESET_POINTER(MakeFunctionCallableWithInterp);
//         RESET_POINTER(IsConstMethod);
//         RESET_POINTER(GetFunctionArgDefault);
//         RESET_POINTER(GetFunctionArgName);
//         RESET_POINTER(GetSpellingFromOperator);
//         RESET_POINTER(GetOperatorFromSpelling);
//         RESET_POINTER(GetOperatorArity);
//         RESET_POINTER(GetOperator);
//         RESET_POINTER(CreateInterpreter);
//         RESET_POINTER(DeleteInterpreter);
//         RESET_POINTER(ActivateInterpreter);
//         RESET_POINTER(GetInterpreter);
//         RESET_POINTER(UseExternalInterpreter);
//         RESET_POINTER(AddSearchPath);
//         RESET_POINTER(GetResourceDir);
//         RESET_POINTER(DetectResourceDir);
//         RESET_POINTER(DetectSystemCompilerIncludePaths);
//         RESET_POINTER(AddIncludePath);
//         RESET_POINTER(GetIncludePaths);
//         RESET_POINTER(Declare);
//         RESET_POINTER(Process);
//         RESET_POINTER(Evaluate);
//         RESET_POINTER(LookupLibrary);
//         RESET_POINTER(LoadLibrary);
//         RESET_POINTER(UnloadLibrary);
//         RESET_POINTER(SearchLibrariesForSymbol);
//         RESET_POINTER(InsertOrReplaceJitSymbol);

// #undef RESET_POINTER
//     }
// }

// #undef LOAD_SYMBOL

// } // namespace Cpp
