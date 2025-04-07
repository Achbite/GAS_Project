// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AnabiosisOrigin/Public/AnabiosisOriginTypes.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ANABIOSISORIGIN_AnabiosisOriginTypes_generated_h
#error "AnabiosisOriginTypes.generated.h already included, missing '#pragma once' in AnabiosisOriginTypes.h"
#endif
#define ANABIOSISORIGIN_AnabiosisOriginTypes_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_AnabiosisOriginTypes_h


#define FOREACH_ENUM_EANABIOSISDEBUGCATEGORY(op) \
	op(EAnabiosisDebugCategory::None) \
	op(EAnabiosisDebugCategory::Abilities) \
	op(EAnabiosisDebugCategory::Combat) \
	op(EAnabiosisDebugCategory::Movement) \
	op(EAnabiosisDebugCategory::Camera) \
	op(EAnabiosisDebugCategory::All) 

enum class EAnabiosisDebugCategory : uint8;
template<> struct TIsUEnumClass<EAnabiosisDebugCategory> { enum { Value = true }; };
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EAnabiosisDebugCategory>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
