#include "tcl.h"
#include <string>
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

#ifndef MODULE_SCOPE
#define MODULE_SCOPE extern
#endif

MODULE_SCOPE int	GetBasicBlockFromObj(Tcl_Interp *interp,
			    Tcl_Obj *obj, llvm::BasicBlock *&block);
MODULE_SCOPE int	GetBuilderFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::IRBuilder<> *&builder);
MODULE_SCOPE int	GetDIBuilderFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::DIBuilder *&ref);
MODULE_SCOPE int	GetEngineFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::ExecutionEngine *&engine);
MODULE_SCOPE int	GetModuleFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::Module *&module);
MODULE_SCOPE std::string GetRefName(std::string prefix);
MODULE_SCOPE int	GetTypeFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::Type *&type);
MODULE_SCOPE int	GetValueFromObj(Tcl_Interp *interp, Tcl_Obj *obj,
			    llvm::Value *&module);
MODULE_SCOPE Tcl_Obj *	NewValueObj(llvm::Value *value);

extern "C" double	__powidf2(double a, int b);

#define DECL_CMD(cName) \
    MODULE_SCOPE int cName(ClientData clientData, Tcl_Interp *interp, \
	    int objc, Tcl_Obj *const objv[])

DECL_CMD(BuildDbgValue);
DECL_CMD(CreateDebugBuilder);
DECL_CMD(DisposeDebugBuilder);
DECL_CMD(DefineCompileUnit);
DECL_CMD(DefineFile);
DECL_CMD(DefineLocation);
DECL_CMD(DefineNamespace);
DECL_CMD(DefineUnspecifiedType);
DECL_CMD(DefineAliasType);
DECL_CMD(DefineArrayType);
DECL_CMD(DefineBasicType);
DECL_CMD(DefinePointerType);
DECL_CMD(DefineStructType);
DECL_CMD(DefineFunctionType);
DECL_CMD(DefineFunction);
DECL_CMD(DefineParameter);
DECL_CMD(DefineLocal);
DECL_CMD(AttachToFunction);
DECL_CMD(SetInstructionLocation);
DECL_CMD(LLVMAddLLVMTclCommandsObjCmd);
DECL_CMD(LLVMAddFunctionAttrObjCmd);
DECL_CMD(LLVMGetFunctionAttrObjCmd);
DECL_CMD(LLVMRemoveFunctionAttrObjCmd);
DECL_CMD(LLVMAddAttributeObjCmd);
DECL_CMD(LLVMRemoveAttributeObjCmd);
DECL_CMD(LLVMGetAttributeObjCmd);
DECL_CMD(LLVMAddInstrAttributeObjCmd);
DECL_CMD(LLVMRemoveInstrAttributeObjCmd);
DECL_CMD(LLVMGetIntrinsicDefinitionObjCmd);
DECL_CMD(LLVMGetIntrinsicIDObjCmd);

template<typename T>//T subclass of llvm::MDNode
MODULE_SCOPE int	GetMetadataFromObj(Tcl_Interp *interp,
			    Tcl_Obj *obj, const char *typeName,
			    T *&ref);
MODULE_SCOPE int	GetLLVMTypeRefFromObj(Tcl_Interp*, Tcl_Obj*,
			    LLVMTypeRef&);
MODULE_SCOPE int	GetLLVMValueRefFromObj(Tcl_Interp*, Tcl_Obj*,
			    LLVMValueRef&);
template<typename T>//T subclass of llvm::Type
static inline int
GetTypeFromObj(
    Tcl_Interp *interp,
    Tcl_Obj *obj,
    std::string msg,
    T *&type)
{
    LLVMTypeRef typeref;
    if (GetLLVMTypeRefFromObj(interp, obj, typeref) != TCL_OK)
	return TCL_ERROR;
    if (!(type = llvm::dyn_cast<T>(llvm::unwrap(typeref)))) {
	Tcl_SetObjResult(interp,
		Tcl_NewStringObj(msg.c_str(), msg.size()));
	return TCL_ERROR;
    }
    return TCL_OK;
}

template<typename T>//T subclass of llvm::Value
static inline int
GetValueFromObj(
    Tcl_Interp *interp,
    Tcl_Obj *obj,
    std::string msg,
    T *&value)
{
    LLVMValueRef valref;
    if (GetLLVMValueRefFromObj(interp, obj, valref) != TCL_OK)
	return TCL_ERROR;
    if (!(value = llvm::dyn_cast<T>(llvm::unwrap(valref)))) {
	Tcl_SetObjResult(interp,
		Tcl_NewStringObj(msg.c_str(), msg.size()));
	return TCL_ERROR;
    }
    return TCL_OK;
}

static inline void
SetStringResult(
    Tcl_Interp *interp,
    std::string msg)
{
    Tcl_SetObjResult(interp, Tcl_NewStringObj(msg.c_str(), msg.size()));
}

MODULE_SCOPE Tcl_Obj* SetLLVMValueRefAsObj(
	Tcl_Interp* interp, LLVMValueRef ref);

static inline Tcl_Obj* SetLLVMValueRefAsObj(
	Tcl_Interp* interp, llvm::Value *value) {
    return SetLLVMValueRefAsObj(interp, llvm::wrap(value));
}

/*
 * Local Variables:
 * mode: c++
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */
