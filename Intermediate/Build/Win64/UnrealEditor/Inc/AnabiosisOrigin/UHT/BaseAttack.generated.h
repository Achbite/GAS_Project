// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/Abilities/BaseAttack.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ANABIOSISORIGIN_BaseAttack_generated_h
#error "BaseAttack.generated.h already included, missing '#pragma once' in BaseAttack.h"
#endif
#define ANABIOSISORIGIN_BaseAttack_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleMontageBlendOut); \
	DECLARE_FUNCTION(execHandleMontageInterrupted); \
	DECLARE_FUNCTION(execHandleMontageCancelled); \
	DECLARE_FUNCTION(execHandleMontageCompleted);


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseAttack(); \
	friend struct Z_Construct_UClass_UBaseAttack_Statics; \
public: \
	DECLARE_CLASS(UBaseAttack, UGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnabiosisOrigin"), NO_API) \
	DECLARE_SERIALIZER(UBaseAttack)


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UBaseAttack(UBaseAttack&&); \
	UBaseAttack(const UBaseAttack&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseAttack); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseAttack); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UBaseAttack) \
	NO_API virtual ~UBaseAttack();


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_43_PROLOG
#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_INCLASS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_46_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ANABIOSISORIGIN_API UClass* StaticClass<class UBaseAttack>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
