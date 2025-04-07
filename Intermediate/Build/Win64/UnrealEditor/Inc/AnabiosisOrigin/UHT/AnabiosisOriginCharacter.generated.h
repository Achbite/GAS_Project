// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EAnabiosisPlayerClass : uint8;
struct FGameplayTag;
#ifdef ANABIOSISORIGIN_AnabiosisOriginCharacter_generated_h
#error "AnabiosisOriginCharacter.generated.h already included, missing '#pragma once' in AnabiosisOriginCharacter.h"
#endif
#define ANABIOSISORIGIN_AnabiosisOriginCharacter_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnRep_CurrentClass); \
	DECLARE_FUNCTION(execRefreshAbilityBindings); \
	DECLARE_FUNCTION(execGetPlayerClass); \
	DECLARE_FUNCTION(execSetPlayerClass); \
	DECLARE_FUNCTION(execSetAttackAbilityTag); \
	DECLARE_FUNCTION(execGetAttackAbilityTag);


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAnabiosisOriginCharacter(); \
	friend struct Z_Construct_UClass_AAnabiosisOriginCharacter_Statics; \
public: \
	DECLARE_CLASS(AAnabiosisOriginCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AnabiosisOrigin"), NO_API) \
	DECLARE_SERIALIZER(AAnabiosisOriginCharacter) \
	virtual UObject* _getUObject() const override { return const_cast<AAnabiosisOriginCharacter*>(this); } \
	NO_API void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CurrentClass=NETFIELD_REP_START, \
		NETFIELD_REP_END=CurrentClass	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AAnabiosisOriginCharacter(AAnabiosisOriginCharacter&&); \
	AAnabiosisOriginCharacter(const AAnabiosisOriginCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAnabiosisOriginCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAnabiosisOriginCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAnabiosisOriginCharacter) \
	NO_API virtual ~AAnabiosisOriginCharacter();


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_37_PROLOG
#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_INCLASS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_40_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ANABIOSISORIGIN_API UClass* StaticClass<class AAnabiosisOriginCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
