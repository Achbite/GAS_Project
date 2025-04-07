// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ANABIOSISORIGIN_EnemyBaseCharacter_generated_h
#error "EnemyBaseCharacter.generated.h already included, missing '#pragma once' in EnemyBaseCharacter.h"
#endif
#define ANABIOSISORIGIN_EnemyBaseCharacter_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyBaseCharacter(); \
	friend struct Z_Construct_UClass_AEnemyBaseCharacter_Statics; \
public: \
	DECLARE_CLASS(AEnemyBaseCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AnabiosisOrigin"), NO_API) \
	DECLARE_SERIALIZER(AEnemyBaseCharacter) \
	virtual UObject* _getUObject() const override { return const_cast<AEnemyBaseCharacter*>(this); }


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_42_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AEnemyBaseCharacter(AEnemyBaseCharacter&&); \
	AEnemyBaseCharacter(const AEnemyBaseCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyBaseCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyBaseCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyBaseCharacter) \
	NO_API virtual ~AEnemyBaseCharacter();


#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_39_PROLOG
#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_42_INCLASS_NO_PURE_DECLS \
	FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_42_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ANABIOSISORIGIN_API UClass* StaticClass<class AEnemyBaseCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
