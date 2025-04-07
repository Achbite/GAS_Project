// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EAnabiosisDebugCategory : uint8;
#ifdef ANABIOSISORIGIN_AnabiosisOriginGameMode_generated_h
#error "AnabiosisOriginGameMode.generated.h already included, missing '#pragma once' in AnabiosisOriginGameMode.h"
#endif
#define ANABIOSISORIGIN_AnabiosisOriginGameMode_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsDebugCategoryEnabled); \
	DECLARE_FUNCTION(execSetDebugCategoryEnabled);


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAnabiosisOriginGameMode(); \
	friend struct Z_Construct_UClass_AAnabiosisOriginGameMode_Statics; \
public: \
	DECLARE_CLASS(AAnabiosisOriginGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/AnabiosisOrigin"), ANABIOSISORIGIN_API) \
	DECLARE_SERIALIZER(AAnabiosisOriginGameMode)


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AAnabiosisOriginGameMode(AAnabiosisOriginGameMode&&); \
	AAnabiosisOriginGameMode(const AAnabiosisOriginGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ANABIOSISORIGIN_API, AAnabiosisOriginGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAnabiosisOriginGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAnabiosisOriginGameMode) \
	ANABIOSISORIGIN_API virtual ~AAnabiosisOriginGameMode();


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_22_PROLOG
#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_INCLASS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ANABIOSISORIGIN_API UClass* StaticClass<class AAnabiosisOriginGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
