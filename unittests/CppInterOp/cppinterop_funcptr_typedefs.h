//--------------------------------------------------------------------*- C++ -*-
// typedefs for function pointers with signatures matching required CppInterOp API
//-----------------------------------------------------------------------------

#ifndef CPPINTEROP_FUNC_PTR_TYPEDEFS_H
#define CPPINTEROP_FUNC_PTR_TYPEDEFS_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Cpp {

using TCppIndex_t = size_t;
using TCppScope_t = void*;
using TCppConstScope_t = const void*;
using TCppType_t = void*;
using TCppFunction_t = void*;
using TCppConstFunction_t = const void*;
using TCppFuncAddr_t = void*;
using TInterp_t = void*;
using TCppObject_t = void*;

enum QualKind : unsigned char {
    Const = 1 << 0,
    Volatile = 1 << 1,
    Restrict = 1 << 2
};

enum Operator : unsigned char {
    OP_None,
    OP_New,
    OP_Delete,
    // ... fill
};

enum OperatorArity : unsigned char { kUnary = 1, kBinary, kBoth };

using GetVersionFunc = std::string (*)();

using DemangleFunc = std::string (*)(const std::string& mangled_name);

using EnableDebugOutputFunc = void (*)(bool value);

using IsDebugOutputEnabledFunc = bool (*)();

using IsAggregateFunc = bool (*)(TCppScope_t scope);

using IsNamespaceFunc = bool (*)(TCppScope_t scope);

using IsClassFunc = bool (*)(TCppScope_t scope);

using IsFunctionFunc = bool (*)(TCppScope_t scope);

using IsFunctionPointerTypeFunc = bool (*)(TCppType_t type);

using IsClassPolymorphicFunc = bool (*)(TCppScope_t klass);

using IsCompleteFunc = bool (*)(TCppScope_t scope);

using SizeOfFunc = size_t (*)(TCppScope_t scope);

using IsBuiltinFunc = bool (*)(TCppType_t type);

using IsTemplateFunc = bool (*)(TCppScope_t handle);

using IsTemplateSpecializationFunc = bool (*)(TCppScope_t handle);

using IsTypedefedFunc = bool (*)(TCppScope_t handle);

using IsAbstractFunc = bool (*)(TCppType_t klass);

using IsEnumScopeFunc = bool (*)(TCppScope_t handle);

using IsEnumConstantFunc = bool (*)(TCppScope_t handle);

using IsEnumTypeFunc = bool (*)(TCppType_t type);

using HasTypeQualifierFunc = bool (*)(TCppType_t type, QualKind qual);

using RemoveTypeQualifierFunc = TCppType_t (*)(TCppType_t type, QualKind qual);

using AddTypeQualifierFunc = TCppType_t (*)(TCppType_t type, QualKind qual);

using GetEnumsFunc = void (*)(TCppScope_t scope, std::vector<TCppScope_t>& Result);

using IsSmartPtrTypeFunc = bool (*)(TCppType_t type);

using GetIntegerTypeFromEnumScopeFunc = TCppType_t (*)(TCppScope_t handle);

using GetIntegerTypeFromEnumTypeFunc = TCppType_t (*)(TCppType_t handle);

using GetEnumConstantsFunc = std::vector<TCppScope_t> (*)(TCppScope_t scope);

using GetEnumConstantTypeFunc = TCppType_t (*)(TCppScope_t scope);

using GetEnumConstantValueFunc = TCppIndex_t (*)(TCppScope_t scope);

using GetSizeOfTypeFunc = size_t (*)(TCppType_t type);

using IsVariableFunc = bool (*)(TCppScope_t scope);

using GetNameFunc = std::string (*)(TCppScope_t klass);

using GetCompleteNameFunc = std::string (*)(TCppScope_t klass);

using GetQualifiedNameFunc = std::string (*)(TCppScope_t klass);

using GetQualifiedCompleteNameFunc = std::string (*)(TCppScope_t klass);

using GetUsingNamespacesFunc = std::vector<TCppScope_t> (*)(TCppScope_t scope);

using GetGlobalScopeFunc = TCppScope_t (*)();

using GetUnderlyingScopeFunc = TCppScope_t (*)(TCppScope_t scope);

using GetScopeFunc = TCppScope_t (*)(const std::string& name, TCppScope_t parent);

using GetScopeFromCompleteNameFunc = TCppScope_t (*)(const std::string& name);

using GetNamedFunc = TCppScope_t (*)(const std::string& name, TCppScope_t parent);

using GetParentScopeFunc = TCppScope_t (*)(TCppScope_t scope);

using GetScopeFromTypeFunc = TCppScope_t (*)(TCppType_t type);

using GetNumBasesFunc = TCppIndex_t (*)(TCppScope_t klass);

using GetBaseClassFunc = TCppScope_t (*)(TCppScope_t klass, TCppIndex_t ibase);

using IsSubclassFunc = bool (*)(TCppScope_t derived, TCppScope_t base);

using GetBaseClassOffsetFunc = int64_t (*)(TCppScope_t derived, TCppScope_t base);

using GetClassMethodsFunc = void (*)(TCppScope_t klass, std::vector<TCppScope_t>& methods);

using GetFunctionTemplatedDeclsFunc = void (*)(TCppScope_t klass, std::vector<TCppScope_t>& methods);

using HasDefaultConstructorFunc = bool (*)(TCppScope_t scope);

using GetDefaultConstructorFunc = TCppFunction_t (*)(TCppScope_t scope);

using GetDestructorFunc = TCppFunction_t (*)(TCppScope_t scope);

using GetFunctionsUsingNameFunc = std::vector<TCppFunction_t> (*)(TCppScope_t scope, const std::string& name);

using GetFunctionReturnTypeFunc = TCppType_t (*)(TCppFunction_t func);

using GetFunctionNumArgsFunc = TCppIndex_t (*)(TCppFunction_t func);

using GetFunctionRequiredArgsFunc = TCppIndex_t (*)(TCppConstFunction_t func);

using GetFunctionArgTypeFunc = TCppType_t (*)(TCppFunction_t func, TCppIndex_t iarg);

using GetFunctionSignatureFunc = std::string (*)(TCppFunction_t func);

using IsFunctionDeletedFunc = bool (*)(TCppConstFunction_t function);

using IsTemplatedFunctionFunc = bool (*)(TCppFunction_t func);

using ExistsFunctionTemplateFunc = bool (*)(const std::string& name, TCppScope_t parent);

using GetClassTemplatedMethodsFunc = bool (*)(const std::string& name, TCppScope_t parent, std::vector<TCppFunction_t>& funcs);

using IsMethodFunc = bool (*)(TCppConstFunction_t method);

using IsPublicMethodFunc = bool (*)(TCppFunction_t method);

using IsProtectedMethodFunc = bool (*)(TCppFunction_t method);

using IsPrivateMethodFunc = bool (*)(TCppFunction_t method);

using IsConstructorFunc = bool (*)(TCppConstFunction_t method);

using IsDestructorFunc = bool (*)(TCppConstFunction_t method);

using IsStaticMethodFunc = bool (*)(TCppConstFunction_t method);

using GetFunctionAddressFromNameFunc = TCppFuncAddr_t (*)(const char* mangled_name);

using GetFunctionAddressFromMethodFunc = TCppFuncAddr_t (*)(TCppFunction_t method);

using IsVirtualMethodFunc = bool (*)(TCppFunction_t method);

using GetDatamembersFunc = void (*)(TCppScope_t scope, std::vector<TCppScope_t>& datamembers);

using GetStaticDatamembersFunc = void (*)(TCppScope_t scope, std::vector<TCppScope_t>& datamembers);

using GetEnumConstantDatamembersFunc = void (*)(TCppScope_t scope, std::vector<TCppScope_t>& datamembers, bool include_enum_class);

using LookupDatamemberFunc = TCppScope_t (*)(const std::string& name, TCppScope_t parent);

using IsLambdaClassFunc = bool (*)(TCppType_t type);

using GetVariableTypeFunc = TCppType_t (*)(TCppScope_t var);

using GetVariableOffsetFunc = intptr_t (*)(TCppScope_t var, TCppScope_t parent);

using IsPublicVariableFunc = bool (*)(TCppScope_t var);

using IsProtectedVariableFunc = bool (*)(TCppScope_t var);

using IsPrivateVariableFunc = bool (*)(TCppScope_t var);

using IsStaticVariableFunc = bool (*)(TCppScope_t var);

using IsConstVariableFunc = bool (*)(TCppScope_t var);

using IsRecordTypeFunc = bool (*)(TCppType_t type);

using IsPODTypeFunc = bool (*)(TCppType_t type);

using IsPointerTypeFunc = bool (*)(TCppType_t type);

using GetPointeeTypeFunc = TCppType_t (*)(TCppType_t type);

using IsReferenceTypeFunc = bool (*)(TCppType_t type);

using IsLValueReferenceTypeFunc = bool (*)(TCppType_t type);

using IsRValueReferenceTypeFunc = bool (*)(TCppType_t type);

using GetPointerTypeFunc = TCppType_t (*)(TCppType_t type);

using GetReferencedTypeFunc = TCppType_t (*)(TCppType_t type, bool rvalue);

using GetNonReferenceTypeFunc = TCppType_t (*)(TCppType_t type);

using GetTypeAsStringFunc = std::string (*)(TCppType_t type);

using GetCanonicalTypeFunc = TCppType_t (*)(TCppType_t type);

// TODO : JitCall return type??

using JitCallMakeFunctionCallableFunc = JitCall (*)(TCppConstFunction_t func);

using JitCallMakeFunctionCallableWithInterpFunc = JitCall (*)(TInterp_t interp, TCppConstFunction_t func);

using IsConstMethodFunc = bool (*)(TCppFunction_t method);

using GetFunctionArgDefaultFunc = std::string (*)(TCppFunction_t func, TCppIndex_t param_index);

using GetFunctionArgNameFunc = std::string (*)(TCppFunction_t func, TCppIndex_t param_index);

using GetSpellingFromOperatorFunc = std::string (*)(Operator op);

using GetOperatorFromSpellingFunc = Operator (*)(const std::string& op);

using GetOperatorArityFunc = OperatorArity (*)(TCppFunction_t op);

using GetOperatorFunc = void (*)(TCppScope_t scope, Operator op, std::vector<TCppFunction_t>& operators, OperatorArity kind);

using CreateInterpreterFunc = TInterp_t (*)(const std::vector<std::string>& Args, const std::vector<std::string>& GpuArgs);

using DeleteInterpreterFunc = bool (*)(TInterp_t interp);

using ActivateInterpreterFunc = bool (*)(TInterp_t interp);

using GetInterpreterFunc = TInterp_t (*)();

using UseExternalInterpreterFunc = void (*)(TInterp_t interp);

using AddSearchPathFunc = void (*)(const char* dir, bool isUser, bool prepend);

using GetResourceDirFunc = const char* (*)();

using DetectResourceDirFunc = std::string (*)(const char* ClangBinaryName);

using DetectSystemCompilerIncludePathsFunc = void (*)(std::vector<std::string>& Paths, const char* CompilerName);

using AddIncludePathFunc = void (*)(const char* dir);

using GetIncludePathsFunc = void (*)(std::vector<std::string>& IncludePaths, bool withSystem, bool withFlags);

using DeclareFunc = int (*)(const char* code, bool silent);

using ProcessFunc = int (*)(const char* code);

using EvaluateFunc = intptr_t (*)(const char* code, bool* HadError);

using LookupLibraryFunc = std::string (*)(const char* lib_name);

using LoadLibraryFunc = bool (*)(const char* lib_stem, bool lookup);

using UnloadLibraryFunc = void (*)(const char* lib_stem);

using SearchLibrariesForSymbolFunc = std::string (*)(const char* mangled_name, bool search_system);

using InsertOrReplaceJitSymbolFunc = bool (*)(const char* linker_mangled_name, uint64_t address);

} // namespace Cpp

#endif // CPPINTEROP_FUNC_PTR_TYPEDEFS_H
