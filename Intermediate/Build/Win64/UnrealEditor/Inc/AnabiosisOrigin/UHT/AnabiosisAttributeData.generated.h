// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ANABIOSISORIGIN_AnabiosisAttributeData_generated_h
#error "AnabiosisAttributeData.generated.h already included, missing '#pragma once' in AnabiosisAttributeData.h"
#endif
#define ANABIOSISORIGIN_AnabiosisAttributeData_generated_h

#define FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_49_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics; \
	ANABIOSISORIGIN_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


template<> ANABIOSISORIGIN_API UScriptStruct* StaticStruct<struct FAnabiosisAttributeData>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h


#define FOREACH_ENUM_EANABIOSISPLAYERCLASS(op) \
	op(EAnabiosisPlayerClass::Warrior) \
	op(EAnabiosisPlayerClass::Assassin) \
	op(EAnabiosisPlayerClass::Mage) 

enum class EAnabiosisPlayerClass : uint8;
template<> struct TIsUEnumClass<EAnabiosisPlayerClass> { enum { Value = true }; };
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EAnabiosisPlayerClass>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
