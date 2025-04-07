// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisOriginCharacter() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisOriginCharacter();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisOriginCharacter_NoRegister();
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemInterface_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAttributeSet_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility_NoRegister();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class AAnabiosisOriginCharacter Function GetAttackAbilityTag
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics
{
	struct AnabiosisOriginCharacter_eventGetAttackAbilityTag_Parms
	{
		FGameplayTag ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\x8e\xb7\xe5\x8f\x96\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x8e\xb7\xe5\x8f\x96\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginCharacter_eventGetAttackAbilityTag_Parms, ReturnValue), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(0, nullptr) }; // 1298103297
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "GetAttackAbilityTag", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::AnabiosisOriginCharacter_eventGetAttackAbilityTag_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::AnabiosisOriginCharacter_eventGetAttackAbilityTag_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execGetAttackAbilityTag)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FGameplayTag*)Z_Param__Result=P_THIS->GetAttackAbilityTag();
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function GetAttackAbilityTag

// Begin Class AAnabiosisOriginCharacter Function GetPlayerClass
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics
{
	struct AnabiosisOriginCharacter_eventGetPlayerClass_Parms
	{
		EAnabiosisPlayerClass ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Character|Class" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\x8e\xb7\xe5\x8f\x96\xe5\xbd\x93\xe5\x89\x8d\xe8\x81\x8c\xe4\xb8\x9a */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x8e\xb7\xe5\x8f\x96\xe5\xbd\x93\xe5\x89\x8d\xe8\x81\x8c\xe4\xb8\x9a" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginCharacter_eventGetPlayerClass_Parms, ReturnValue), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass, METADATA_PARAMS(0, nullptr) }; // 634283710
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "GetPlayerClass", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::AnabiosisOriginCharacter_eventGetPlayerClass_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::AnabiosisOriginCharacter_eventGetPlayerClass_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execGetPlayerClass)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EAnabiosisPlayerClass*)Z_Param__Result=P_THIS->GetPlayerClass();
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function GetPlayerClass

// Begin Class AAnabiosisOriginCharacter Function OnRep_CurrentClass
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xa4\x84\xe7\x90\x86\xe8\x81\x8c\xe4\xb8\x9a\xe5\x8f\x98\xe5\x8c\x96\xe7\x9a\x84\xe7\xbd\x91\xe7\xbb\x9c\xe5\xa4\x8d\xe5\x88\xb6 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa4\x84\xe7\x90\x86\xe8\x81\x8c\xe4\xb8\x9a\xe5\x8f\x98\xe5\x8c\x96\xe7\x9a\x84\xe7\xbd\x91\xe7\xbb\x9c\xe5\xa4\x8d\xe5\x88\xb6" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "OnRep_CurrentClass", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execOnRep_CurrentClass)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnRep_CurrentClass();
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function OnRep_CurrentClass

// Begin Class AAnabiosisOriginCharacter Function RefreshAbilityBindings
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x88\xb7\xe6\x96\xb0\xe8\x83\xbd\xe5\x8a\x9b\xe8\xbe\x93\xe5\x85\xa5\xe7\xbb\x91\xe5\xae\x9a */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\xb7\xe6\x96\xb0\xe8\x83\xbd\xe5\x8a\x9b\xe8\xbe\x93\xe5\x85\xa5\xe7\xbb\x91\xe5\xae\x9a" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "RefreshAbilityBindings", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execRefreshAbilityBindings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshAbilityBindings();
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function RefreshAbilityBindings

// Begin Class AAnabiosisOriginCharacter Function SetAttackAbilityTag
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics
{
	struct AnabiosisOriginCharacter_eventSetAttackAbilityTag_Parms
	{
		FGameplayTag NewTag;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xae\xbe\xe7\xbd\xae\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xae\xbe\xe7\xbd\xae\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewTag;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::NewProp_NewTag = { "NewTag", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginCharacter_eventSetAttackAbilityTag_Parms, NewTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewTag_MetaData), NewProp_NewTag_MetaData) }; // 1298103297
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::NewProp_NewTag,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "SetAttackAbilityTag", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::AnabiosisOriginCharacter_eventSetAttackAbilityTag_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::AnabiosisOriginCharacter_eventSetAttackAbilityTag_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execSetAttackAbilityTag)
{
	P_GET_STRUCT_REF(FGameplayTag,Z_Param_Out_NewTag);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAttackAbilityTag(Z_Param_Out_NewTag);
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function SetAttackAbilityTag

// Begin Class AAnabiosisOriginCharacter Function SetPlayerClass
struct Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics
{
	struct AnabiosisOriginCharacter_eventSetPlayerClass_Parms
	{
		EAnabiosisPlayerClass NewClass;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Character|Class" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xae\xbe\xe7\xbd\xae\xe8\xa7\x92\xe8\x89\xb2\xe8\x81\x8c\xe4\xb8\x9a */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xae\xbe\xe7\xbd\xae\xe8\xa7\x92\xe8\x89\xb2\xe8\x81\x8c\xe4\xb8\x9a" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewClass_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::NewProp_NewClass_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::NewProp_NewClass = { "NewClass", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginCharacter_eventSetPlayerClass_Parms, NewClass), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass, METADATA_PARAMS(0, nullptr) }; // 634283710
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::NewProp_NewClass_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::NewProp_NewClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginCharacter, nullptr, "SetPlayerClass", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::AnabiosisOriginCharacter_eventSetPlayerClass_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::AnabiosisOriginCharacter_eventSetPlayerClass_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginCharacter::execSetPlayerClass)
{
	P_GET_ENUM(EAnabiosisPlayerClass,Z_Param_NewClass);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetPlayerClass(EAnabiosisPlayerClass(Z_Param_NewClass));
	P_NATIVE_END;
}
// End Class AAnabiosisOriginCharacter Function SetPlayerClass

// Begin Class AAnabiosisOriginCharacter
void AAnabiosisOriginCharacter::StaticRegisterNativesAAnabiosisOriginCharacter()
{
	UClass* Class = AAnabiosisOriginCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetAttackAbilityTag", &AAnabiosisOriginCharacter::execGetAttackAbilityTag },
		{ "GetPlayerClass", &AAnabiosisOriginCharacter::execGetPlayerClass },
		{ "OnRep_CurrentClass", &AAnabiosisOriginCharacter::execOnRep_CurrentClass },
		{ "RefreshAbilityBindings", &AAnabiosisOriginCharacter::execRefreshAbilityBindings },
		{ "SetAttackAbilityTag", &AAnabiosisOriginCharacter::execSetAttackAbilityTag },
		{ "SetPlayerClass", &AAnabiosisOriginCharacter::execSetPlayerClass },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAnabiosisOriginCharacter);
UClass* Z_Construct_UClass_AAnabiosisOriginCharacter_NoRegister()
{
	return AAnabiosisOriginCharacter::StaticClass();
}
struct Z_Construct_UClass_AAnabiosisOriginCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\xb8\xb8\xe6\x88\x8f\xe4\xb8\xbb\xe8\xa7\x92\xe8\x89\xb2\xe7\xb1\xbb\n * \xe5\xae\x9e\xe7\x8e\xb0\xe5\x9f\xba\xe7\xa1\x80\xe7\xa7\xbb\xe5\x8a\xa8\xe3\x80\x81\xe8\xa7\x86\xe8\xa7\x92\xe5\x92\x8c\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb3\xbb\xe7\xbb\x9f\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb8\xb8\xe6\x88\x8f\xe4\xb8\xbb\xe8\xa7\x92\xe8\x89\xb2\xe7\xb1\xbb\n\xe5\xae\x9e\xe7\x8e\xb0\xe5\x9f\xba\xe7\xa1\x80\xe7\xa7\xbb\xe5\x8a\xa8\xe3\x80\x81\xe8\xa7\x86\xe8\xa7\x92\xe5\x92\x8c\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb3\xbb\xe7\xbb\x9f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\x9b\xb8\xe6\x9c\xba\xe8\x87\x82\xe7\xbb\x84\xe4\xbb\xb6\xef\xbc\x9a\xe6\x8e\xa7\xe5\x88\xb6\xe7\x9b\xb8\xe6\x9c\xba\xe8\xb7\x9f\xe9\x9a\x8f\xe8\xb7\x9d\xe7\xa6\xbb\xe5\x92\x8c\xe4\xbd\x8d\xe7\xbd\xae */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe8\x87\x82\xe7\xbb\x84\xe4\xbb\xb6\xef\xbc\x9a\xe6\x8e\xa7\xe5\x88\xb6\xe7\x9b\xb8\xe6\x9c\xba\xe8\xb7\x9f\xe9\x9a\x8f\xe8\xb7\x9d\xe7\xa6\xbb\xe5\x92\x8c\xe4\xbd\x8d\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xb7\x9f\xe9\x9a\x8f\xe7\x9b\xb8\xe6\x9c\xba\xef\xbc\x9a\xe5\xae\x9e\xe7\x8e\xb0\xe7\xac\xac\xe4\xb8\x89\xe4\xba\xba\xe7\xa7\xb0\xe8\xa7\x86\xe8\xa7\x92 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb7\x9f\xe9\x9a\x8f\xe7\x9b\xb8\xe6\x9c\xba\xef\xbc\x9a\xe5\xae\x9e\xe7\x8e\xb0\xe7\xac\xac\xe4\xb8\x89\xe4\xba\xba\xe7\xa7\xb0\xe8\xa7\x86\xe8\xa7\x92" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbilitySystemComponent_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** GAS\xe7\xb3\xbb\xe7\xbb\x9f\xe7\xbb\x84\xe4\xbb\xb6 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GAS\xe7\xb3\xbb\xe7\xbb\x9f\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttributeSet_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xb1\x9e\xe6\x80\xa7\xe9\x9b\x86 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb1\x9e\xe6\x80\xa7\xe9\x9b\x86" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackAbilityTag_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultAbilities_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\xbb\x98\xe8\xae\xa4\xe8\x83\xbd\xe5\x8a\x9b\xe5\x88\x97\xe8\xa1\xa8 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\xbb\x98\xe8\xae\xa4\xe8\x83\xbd\xe5\x8a\x9b\xe5\x88\x97\xe8\xa1\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClassAttributeTable_MetaData[] = {
		{ "Category", "Character|Class" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae\xe8\xa1\xa8\xe5\xbc\x95\xe7\x94\xa8 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae\xe8\xa1\xa8\xe5\xbc\x95\xe7\x94\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentClass_MetaData[] = {
		{ "Category", "Character|Class" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xbd\x93\xe5\x89\x8d\xe8\xa7\x92\xe8\x89\xb2\xe8\x81\x8c\xe4\xb8\x9a */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/AnabiosisOriginCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe8\xa7\x92\xe8\x89\xb2\xe8\x81\x8c\xe4\xb8\x9a" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AbilitySystemComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttributeSet;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AttackAbilityTag;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DefaultAbilities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultAbilities;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ClassAttributeTable;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentClass_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_GetAttackAbilityTag, "GetAttackAbilityTag" }, // 2204421821
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_GetPlayerClass, "GetPlayerClass" }, // 3549803049
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_OnRep_CurrentClass, "OnRep_CurrentClass" }, // 19381623
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_RefreshAbilityBindings, "RefreshAbilityBindings" }, // 4009325131
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_SetAttackAbilityTag, "SetAttackAbilityTag" }, // 3860974097
		{ &Z_Construct_UFunction_AAnabiosisOriginCharacter_SetPlayerClass, "SetPlayerClass" }, // 392598667
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAnabiosisOriginCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbilitySystemComponent_MetaData), NewProp_AbilitySystemComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AttributeSet = { "AttributeSet", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, AttributeSet), Z_Construct_UClass_UAttributeSet_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttributeSet_MetaData), NewProp_AttributeSet_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AttackAbilityTag = { "AttackAbilityTag", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, AttackAbilityTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackAbilityTag_MetaData), NewProp_AttackAbilityTag_MetaData) }; // 1298103297
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_DefaultAbilities_Inner = { "DefaultAbilities", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_UGameplayAbility_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_DefaultAbilities = { "DefaultAbilities", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, DefaultAbilities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultAbilities_MetaData), NewProp_DefaultAbilities_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_ClassAttributeTable = { "ClassAttributeTable", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, ClassAttributeTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClassAttributeTable_MetaData), NewProp_ClassAttributeTable_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CurrentClass_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CurrentClass = { "CurrentClass", "OnRep_CurrentClass", (EPropertyFlags)0x0020080100000025, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginCharacter, CurrentClass), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentClass_MetaData), NewProp_CurrentClass_MetaData) }; // 634283710
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AbilitySystemComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AttributeSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_AttackAbilityTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_DefaultAbilities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_DefaultAbilities,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_ClassAttributeTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CurrentClass_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::NewProp_CurrentClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UAbilitySystemInterface_NoRegister, (int32)VTABLE_OFFSET(AAnabiosisOriginCharacter, IAbilitySystemInterface), false },  // 2272790346
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::ClassParams = {
	&AAnabiosisOriginCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAnabiosisOriginCharacter()
{
	if (!Z_Registration_Info_UClass_AAnabiosisOriginCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAnabiosisOriginCharacter.OuterSingleton, Z_Construct_UClass_AAnabiosisOriginCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAnabiosisOriginCharacter.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<AAnabiosisOriginCharacter>()
{
	return AAnabiosisOriginCharacter::StaticClass();
}
void AAnabiosisOriginCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
{
	static const FName Name_CurrentClass(TEXT("CurrentClass"));
	const bool bIsValid = true
		&& Name_CurrentClass == ClassReps[(int32)ENetFields_Private::CurrentClass].Property->GetFName();
	checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AAnabiosisOriginCharacter"));
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAnabiosisOriginCharacter);
AAnabiosisOriginCharacter::~AAnabiosisOriginCharacter() {}
// End Class AAnabiosisOriginCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAnabiosisOriginCharacter, AAnabiosisOriginCharacter::StaticClass, TEXT("AAnabiosisOriginCharacter"), &Z_Registration_Info_UClass_AAnabiosisOriginCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAnabiosisOriginCharacter), 2483387126U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_1969790727(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_AnabiosisOriginCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
