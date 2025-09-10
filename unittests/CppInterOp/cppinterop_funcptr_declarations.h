#ifndef CPPINTEROP_FUNC_PTR_DECLARATIONS_H
#define CPPINTEROP_FUNC_PTR_DECLARATIONS_H

#include "cppinterop_funcptr_typedefs.h"

namespace Cpp{

// Declare function pointers for dynamic binding, e.g., via dlsym or GetProcAddress


// decltype, use types from CppInterOp.h
// no need t extern
// demangling
extern GetVersionFunc pGetVersion;

extern DemangleFunc pDemangle;

extern EnableDebugOutputFunc pEnableDebugOutput;

extern IsDebugOutputEnabledFunc pIsDebugOutputEnabled;

extern IsAggregateFunc pIsAggregate;

extern IsNamespaceFunc pIsNamespace;

extern IsClassFunc pIsClass;

extern IsFunctionFunc pIsFunction;

extern IsFunctionPointerTypeFunc pIsFunctionPointerType;

extern IsClassPolymorphicFunc pIsClassPolymorphic;

extern IsCompleteFunc pIsComplete;

extern SizeOfFunc pSizeOf;

extern IsBuiltinFunc pIsBuiltin;

extern IsTemplateFunc pIsTemplate;

extern IsTemplateSpecializationFunc pIsTemplateSpecialization;

extern IsTypedefedFunc pIsTypedefed;

extern IsAbstractFunc pIsAbstract;

extern IsEnumScopeFunc pIsEnumScope;

extern IsEnumConstantFunc pIsEnumConstant;

extern IsEnumTypeFunc pIsEnumType;

extern HasTypeQualifierFunc pHasTypeQualifier;

extern RemoveTypeQualifierFunc pRemoveTypeQualifier;

extern AddTypeQualifierFunc pAddTypeQualifier;

extern GetEnumsFunc pGetEnums;

extern IsSmartPtrTypeFunc pIsSmartPtrType;

extern GetIntegerTypeFromEnumScopeFunc pGetIntegerTypeFromEnumScope;

extern GetIntegerTypeFromEnumTypeFunc pGetIntegerTypeFromEnumType;

extern GetEnumConstantsFunc pGetEnumConstants;

extern GetEnumConstantTypeFunc pGetEnumConstantType;

extern GetEnumConstantValueFunc pGetEnumConstantValue;

extern GetSizeOfTypeFunc pGetSizeOfType;

extern IsVariableFunc pIsVariable;

extern GetNameFunc pGetName;

extern GetCompleteNameFunc pGetCompleteName;

extern GetQualifiedNameFunc pGetQualifiedName;

extern GetQualifiedCompleteNameFunc pGetQualifiedCompleteName;

extern GetUsingNamespacesFunc pGetUsingNamespaces;

extern GetGlobalScopeFunc pGetGlobalScope;

extern GetUnderlyingScopeFunc pGetUnderlyingScope;

extern GetScopeFunc pGetScope;

extern GetScopeFromCompleteNameFunc pGetScopeFromCompleteName;

extern GetNamedFunc pGetNamed;

extern GetParentScopeFunc pGetParentScope;

extern GetScopeFromTypeFunc pGetScopeFromType;

extern GetNumBasesFunc pGetNumBases;

extern GetBaseClassFunc pGetBaseClass;

extern IsSubclassFunc pIsSubclass;

extern GetBaseClassOffsetFunc pGetBaseClassOffset;

extern GetClassMethodsFunc pGetClassMethods;

extern GetFunctionTemplatedDeclsFunc pGetFunctionTemplatedDecls;

extern HasDefaultConstructorFunc pHasDefaultConstructor;

extern GetDefaultConstructorFunc pGetDefaultConstructor;

extern GetDestructorFunc pGetDestructor;

extern GetFunctionsUsingNameFunc pGetFunctionsUsingName;

extern GetFunctionReturnTypeFunc pGetFunctionReturnType;

extern GetFunctionNumArgsFunc pGetFunctionNumArgs;

extern GetFunctionRequiredArgsFunc pGetFunctionRequiredArgs;

extern GetFunctionArgTypeFunc pGetFunctionArgType;

extern GetFunctionSignatureFunc pGetFunctionSignature;

extern IsFunctionDeletedFunc pIsFunctionDeleted;

extern IsTemplatedFunctionFunc pIsTemplatedFunction;

extern ExistsFunctionTemplateFunc pExistsFunctionTemplate;

extern GetClassTemplatedMethodsFunc pGetClassTemplatedMethods;

extern IsMethodFunc pIsMethod;

extern IsPublicMethodFunc pIsPublicMethod;

extern IsProtectedMethodFunc pIsProtectedMethod;

extern IsPrivateMethodFunc pIsPrivateMethod;

extern IsConstructorFunc pIsConstructor;

extern IsDestructorFunc pIsDestructor;

extern IsStaticMethodFunc pIsStaticMethod;

extern GetFunctionAddressFromNameFunc pGetFunctionAddressFromName;

extern GetFunctionAddressFromMethodFunc pGetFunctionAddressFromMethod;

extern IsVirtualMethodFunc pIsVirtualMethod;

extern GetDatamembersFunc pGetDatamembers;

extern GetStaticDatamembersFunc pGetStaticDatamembers;

extern GetEnumConstantDatamembersFunc pGetEnumConstantDatamembers;

extern LookupDatamemberFunc pLookupDatamember;

extern IsLambdaClassFunc pIsLambdaClass;

extern GetVariableTypeFunc pGetVariableType;

extern GetVariableOffsetFunc pGetVariableOffset;

extern IsPublicVariableFunc pIsPublicVariable;

extern IsProtectedVariableFunc pIsProtectedVariable;

extern IsPrivateVariableFunc pIsPrivateVariable;

extern IsStaticVariableFunc pIsStaticVariable;

extern IsConstVariableFunc pIsConstVariable;

extern IsRecordTypeFunc pIsRecordType;

extern IsPODTypeFunc pIsPODType;

extern IsPointerTypeFunc pIsPointerType;

extern GetPointeeTypeFunc pGetPointeeType;

extern IsReferenceTypeFunc pIsReferenceType;

extern IsLValueReferenceTypeFunc pIsLValueReferenceType;

extern IsRValueReferenceTypeFunc pIsRValueReferenceType;

extern GetPointerTypeFunc pGetPointerType;

extern GetReferencedTypeFunc pGetReferencedType;

extern GetNonReferenceTypeFunc pGetNonReferenceType;

extern GetTypeAsStringFunc pGetTypeAsString;

extern GetCanonicalTypeFunc pGetCanonicalType;

extern JitCallMakeFunctionCallableFunc pMakeFunctionCallable;

// extern JitCallMakeFunctionCallableWithInterpFunc pMakeFunctionCallableWithInterp;

extern IsConstMethodFunc pIsConstMethod;

extern GetFunctionArgDefaultFunc pGetFunctionArgDefault;

extern GetFunctionArgNameFunc pGetFunctionArgName;

extern GetSpellingFromOperatorFunc pGetSpellingFromOperator;

extern GetOperatorFromSpellingFunc pGetOperatorFromSpelling;

extern GetOperatorArityFunc pGetOperatorArity;

extern GetOperatorFunc pGetOperator;

extern CreateInterpreterFunc pCreateInterpreter;

extern DeleteInterpreterFunc pDeleteInterpreter;

extern ActivateInterpreterFunc pActivateInterpreter;

extern GetInterpreterFunc pGetInterpreter;

extern UseExternalInterpreterFunc pUseExternalInterpreter;

extern AddSearchPathFunc pAddSearchPath;

extern GetResourceDirFunc pGetResourceDir;

extern DetectResourceDirFunc pDetectResourceDir;

extern DetectSystemCompilerIncludePathsFunc pDetectSystemCompilerIncludePaths;

extern AddIncludePathFunc pAddIncludePath;

extern GetIncludePathsFunc pGetIncludePaths;

extern DeclareFunc pDeclare;

extern ProcessFunc pProcess;

extern EvaluateFunc pEvaluate;

extern LookupLibraryFunc pLookupLibrary;

extern LoadLibraryFunc pLoadLibrary;

extern UnloadLibraryFunc pUnloadLibrary;

extern SearchLibrariesForSymbolFunc pSearchLibrariesForSymbol;

extern InsertOrReplaceJitSymbolFunc pInsertOrReplaceJitSymbol;

} // namespace Cpp

#endif // CPPINTEROP_FUNC_PTR_DECLARATIONS_H
