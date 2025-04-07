// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisAttributeData() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass();
ANABIOSISORIGIN_API UScriptStruct* Z_Construct_UScriptStruct_FAnabiosisAttributeData();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Enum EAnabiosisPlayerClass
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EAnabiosisPlayerClass;
static UEnum* EAnabiosisPlayerClass_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EAnabiosisPlayerClass.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EAnabiosisPlayerClass.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("EAnabiosisPlayerClass"));
	}
	return Z_Registration_Info_UEnum_EAnabiosisPlayerClass.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EAnabiosisPlayerClass>()
{
	return EAnabiosisPlayerClass_StaticEnum();
}
struct Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Assassin.DisplayName", "\xe5\x88\xba\xe5\xae\xa2" },
		{ "Assassin.Name", "EAnabiosisPlayerClass::Assassin" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe7\x8e\xa9\xe5\xae\xb6\xe8\x81\x8c\xe4\xb8\x9a\xe7\xb1\xbb\xe5\x9e\x8b\n */" },
#endif
		{ "Mage.DisplayName", "\xe6\xb3\x95\xe5\xb8\x88" },
		{ "Mage.Name", "EAnabiosisPlayerClass::Mage" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x8e\xa9\xe5\xae\xb6\xe8\x81\x8c\xe4\xb8\x9a\xe7\xb1\xbb\xe5\x9e\x8b" },
#endif
		{ "Warrior.DisplayName", "\xe6\x88\x98\xe5\xa3\xab" },
		{ "Warrior.Name", "EAnabiosisPlayerClass::Warrior" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EAnabiosisPlayerClass::Warrior", (int64)EAnabiosisPlayerClass::Warrior },
		{ "EAnabiosisPlayerClass::Assassin", (int64)EAnabiosisPlayerClass::Assassin },
		{ "EAnabiosisPlayerClass::Mage", (int64)EAnabiosisPlayerClass::Mage },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	nullptr,
	"EAnabiosisPlayerClass",
	"EAnabiosisPlayerClass",
	Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass()
{
	if (!Z_Registration_Info_UEnum_EAnabiosisPlayerClass.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EAnabiosisPlayerClass.InnerSingleton, Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EAnabiosisPlayerClass.InnerSingleton;
}
// End Enum EAnabiosisPlayerClass

// Begin ScriptStruct FAnabiosisAttributeData
static_assert(std::is_polymorphic<FAnabiosisAttributeData>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FAnabiosisAttributeData cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_AnabiosisAttributeData;
class UScriptStruct* FAnabiosisAttributeData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnabiosisAttributeData, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("AnabiosisAttributeData"));
	}
	return Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UScriptStruct* StaticStruct<FAnabiosisAttributeData>()
{
	return FAnabiosisAttributeData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\xb8\xb8\xe6\x88\x8f\xe7\x8e\xa9\xe5\xae\xb6\xe7\x9a\x84\xe6\x89\x80\xe6\x9c\x89\xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae\n */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xb8\xb8\xe6\x88\x8f\xe7\x8e\xa9\xe5\xae\xb6\xe7\x9a\x84\xe6\x89\x80\xe6\x9c\x89\xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerClass_MetaData[] = {
		{ "Category", "Basic" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\x81\x8c\xe4\xb8\x9a\xe7\xb1\xbb\xe5\x9e\x8b */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x81\x8c\xe4\xb8\x9a\xe7\xb1\xbb\xe5\x9e\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Level_MetaData[] = {
		{ "Category", "Basic" },
		{ "ClampMax", "99" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xa7\x92\xe8\x89\xb2\xe7\xad\x89\xe7\xba\xa7 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x92\xe8\x89\xb2\xe7\xad\x89\xe7\xba\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Strength_MetaData[] = {
		{ "Category", "Primary Attributes" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8a\x9b\xe9\x87\x8f\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\x9b\xe9\x87\x8f\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Agility_MetaData[] = {
		{ "Category", "Primary Attributes" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x95\x8f\xe6\x8d\xb7\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\xe5\x92\x8c\xe9\x97\xaa\xe9\x81\xbf */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8f\xe6\x8d\xb7\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6\xe5\x92\x8c\xe9\x97\xaa\xe9\x81\xbf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Constitution_MetaData[] = {
		{ "Category", "Primary Attributes" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe4\xbd\x93\xe8\xb4\xa8\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc\xe5\x92\x8c\xe9\x98\xb2\xe5\xbe\xa1 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbd\x93\xe8\xb4\xa8\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc\xe5\x92\x8c\xe9\x98\xb2\xe5\xbe\xa1" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intelligence_MetaData[] = {
		{ "Category", "Primary Attributes" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x99\xba\xe5\x8a\x9b\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe6\x8a\x80\xe8\x83\xbd\xe4\xbc\xa4\xe5\xae\xb3\xe5\x92\x8c\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x99\xba\xe5\x8a\x9b\xef\xbc\x9a\xe5\xbd\xb1\xe5\x93\x8d\xe6\x8a\x80\xe8\x83\xbd\xe4\xbc\xa4\xe5\xae\xb3\xe5\x92\x8c\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x9c\x80\xe5\xa4\xa7\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\x80\xe5\xa4\xa7\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mana_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxMana_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x9c\x80\xe5\xa4\xa7\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9c\x80\xe5\xa4\xa7\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackPower_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Defense_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\x98\xb2\xe5\xbe\xa1\xe5\x8a\x9b */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\x98\xb2\xe5\xbe\xa1\xe5\x8a\x9b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CriticalChance_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMax", "1" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x9a\xb4\xe5\x87\xbb\xe7\x8e\x87 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9a\xb4\xe5\x87\xbb\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CriticalMultiplier_MetaData[] = {
		{ "Category", "Combat Attributes" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x9a\xb4\xe5\x87\xbb\xe4\xbc\xa4\xe5\xae\xb3\xe5\x80\x8d\xe7\x8e\x87 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x9a\xb4\xe5\x87\xbb\xe4\xbc\xa4\xe5\xae\xb3\xe5\x80\x8d\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackPowerPerStrength_MetaData[] = {
		{ "Category", "Attribute Coefficients" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xaf\x8f\xe7\x82\xb9\xe5\x8a\x9b\xe9\x87\x8f\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe7\x82\xb9\xe5\x8a\x9b\xe9\x87\x8f\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\x9b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementSpeedPerAgility_MetaData[] = {
		{ "Category", "Attribute Coefficients" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xaf\x8f\xe7\x82\xb9\xe6\x95\x8f\xe6\x8d\xb7\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe7\x82\xb9\xe6\x95\x8f\xe6\x8d\xb7\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe7\xa7\xbb\xe5\x8a\xa8\xe9\x80\x9f\xe5\xba\xa6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HealthPerConstitution_MetaData[] = {
		{ "Category", "Attribute Coefficients" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xaf\x8f\xe7\x82\xb9\xe4\xbd\x93\xe8\xb4\xa8\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe7\x82\xb9\xe4\xbd\x93\xe8\xb4\xa8\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ManaPerIntelligence_MetaData[] = {
		{ "Category", "Attribute Coefficients" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xaf\x8f\xe7\x82\xb9\xe6\x99\xba\xe5\x8a\x9b\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xaf\x8f\xe7\x82\xb9\xe6\x99\xba\xe5\x8a\x9b\xe6\x8f\x90\xe4\xbe\x9b\xe7\x9a\x84\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttributeGrowthRate_MetaData[] = {
		{ "Category", "Growth" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HealthGrowthRate_MetaData[] = {
		{ "Category", "Growth" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe7\x94\x9f\xe5\x91\xbd\xe5\x80\xbc\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ManaGrowthRate_MetaData[] = {
		{ "Category", "Growth" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/AnabiosisAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xad\x89\xe7\xba\xa7\xe6\x8f\x90\xe5\x8d\x87\xe6\x97\xb6\xe9\xad\x94\xe6\xb3\x95\xe5\x80\xbc\xe6\x88\x90\xe9\x95\xbf\xe7\x8e\x87" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_PlayerClass_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PlayerClass;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Level;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Strength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Agility;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Constitution;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Intelligence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Health;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mana;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxMana;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackPower;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Defense;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CriticalChance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CriticalMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackPowerPerStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MovementSpeedPerAgility;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HealthPerConstitution;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ManaPerIntelligence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttributeGrowthRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HealthGrowthRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ManaGrowthRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnabiosisAttributeData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_PlayerClass_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_PlayerClass = { "PlayerClass", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, PlayerClass), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisPlayerClass, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerClass_MetaData), NewProp_PlayerClass_MetaData) }; // 634283710
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Level = { "Level", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Level), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Level_MetaData), NewProp_Level_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Strength = { "Strength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Strength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Strength_MetaData), NewProp_Strength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Agility = { "Agility", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Agility), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Agility_MetaData), NewProp_Agility_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Constitution = { "Constitution", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Constitution), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Constitution_MetaData), NewProp_Constitution_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Intelligence = { "Intelligence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Intelligence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intelligence_MetaData), NewProp_Intelligence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Health), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Health_MetaData), NewProp_Health_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, MaxHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHealth_MetaData), NewProp_MaxHealth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Mana = { "Mana", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Mana), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mana_MetaData), NewProp_Mana_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MaxMana = { "MaxMana", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, MaxMana), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxMana_MetaData), NewProp_MaxMana_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttackPower = { "AttackPower", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, AttackPower), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackPower_MetaData), NewProp_AttackPower_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Defense = { "Defense", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, Defense), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Defense_MetaData), NewProp_Defense_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_CriticalChance = { "CriticalChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, CriticalChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CriticalChance_MetaData), NewProp_CriticalChance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_CriticalMultiplier = { "CriticalMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, CriticalMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CriticalMultiplier_MetaData), NewProp_CriticalMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttackPowerPerStrength = { "AttackPowerPerStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, AttackPowerPerStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackPowerPerStrength_MetaData), NewProp_AttackPowerPerStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MovementSpeedPerAgility = { "MovementSpeedPerAgility", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, MovementSpeedPerAgility), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementSpeedPerAgility_MetaData), NewProp_MovementSpeedPerAgility_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_HealthPerConstitution = { "HealthPerConstitution", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, HealthPerConstitution), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HealthPerConstitution_MetaData), NewProp_HealthPerConstitution_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_ManaPerIntelligence = { "ManaPerIntelligence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, ManaPerIntelligence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ManaPerIntelligence_MetaData), NewProp_ManaPerIntelligence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttributeGrowthRate = { "AttributeGrowthRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, AttributeGrowthRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttributeGrowthRate_MetaData), NewProp_AttributeGrowthRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_HealthGrowthRate = { "HealthGrowthRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, HealthGrowthRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HealthGrowthRate_MetaData), NewProp_HealthGrowthRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_ManaGrowthRate = { "ManaGrowthRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnabiosisAttributeData, ManaGrowthRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ManaGrowthRate_MetaData), NewProp_ManaGrowthRate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_PlayerClass_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_PlayerClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Level,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Strength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Agility,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Constitution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Intelligence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Health,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MaxHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Mana,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MaxMana,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttackPower,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_Defense,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_CriticalChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_CriticalMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttackPowerPerStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_MovementSpeedPerAgility,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_HealthPerConstitution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_ManaPerIntelligence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_AttributeGrowthRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_HealthGrowthRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewProp_ManaGrowthRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"AnabiosisAttributeData",
	Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::PropPointers),
	sizeof(FAnabiosisAttributeData),
	alignof(FAnabiosisAttributeData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAnabiosisAttributeData()
{
	if (!Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.InnerSingleton, Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_AnabiosisAttributeData.InnerSingleton;
}
// End ScriptStruct FAnabiosisAttributeData

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EAnabiosisPlayerClass_StaticEnum, TEXT("EAnabiosisPlayerClass"), &Z_Registration_Info_UEnum_EAnabiosisPlayerClass, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 634283710U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FAnabiosisAttributeData::StaticStruct, Z_Construct_UScriptStruct_FAnabiosisAttributeData_Statics::NewStructOps, TEXT("AnabiosisAttributeData"), &Z_Registration_Info_UScriptStruct_AnabiosisAttributeData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAnabiosisAttributeData), 2266272469U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_4030859885(TEXT("/Script/AnabiosisOrigin"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_AnabiosisAttributeData_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
