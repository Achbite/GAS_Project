// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/Data/EnemyAttributeData.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ANABIOSISORIGIN_EnemyAttributeData_generated_h
#error "EnemyAttributeData.generated.h already included, missing '#pragma once' in EnemyAttributeData.h"
#endif
#define ANABIOSISORIGIN_EnemyAttributeData_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_62_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FEnemyAttributeData_Statics; \
	ANABIOSISORIGIN_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


template<> ANABIOSISORIGIN_API UScriptStruct* StaticStruct<struct FEnemyAttributeData>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h


#define FOREACH_ENUM_EENEMYTYPE(op) \
	op(EEnemyType::Normal) \
	op(EEnemyType::Elite) \
	op(EEnemyType::Boss) \
	op(EEnemyType::MiniBoss) 

enum class EEnemyType : uint8;
template<> struct TIsUEnumClass<EEnemyType> { enum { Value = true }; };
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EEnemyType>();

#define FOREACH_ENUM_EENEMYBEHAVIORTYPE(op) \
	op(EEnemyBehaviorType::Passive) \
	op(EEnemyBehaviorType::Aggressive) \
	op(EEnemyBehaviorType::Territorial) \
	op(EEnemyBehaviorType::Patrol) 

enum class EEnemyBehaviorType : uint8;
template<> struct TIsUEnumClass<EEnemyBehaviorType> { enum { Value = true }; };
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EEnemyBehaviorType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
