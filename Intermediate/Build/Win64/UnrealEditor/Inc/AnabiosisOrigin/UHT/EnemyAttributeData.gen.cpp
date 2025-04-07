// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Data/EnemyAttributeData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyAttributeData() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType();
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EEnemyType();
ANABIOSISORIGIN_API UScriptStruct* Z_Construct_UScriptStruct_FEnemyAttributeData();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Enum EEnemyType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyType;
static UEnum* EEnemyType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEnemyType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEnemyType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AnabiosisOrigin_EEnemyType, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("EEnemyType"));
	}
	return Z_Registration_Info_UEnum_EEnemyType.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EEnemyType>()
{
	return EEnemyType_StaticEnum();
}
struct Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Boss.DisplayName", "Boss" },
		{ "Boss.Name", "EEnemyType::Boss" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\x95\x8c\xe4\xba\xba\xe7\xb1\xbb\xe5\x9e\x8b\xe6\x9e\x9a\xe4\xb8\xbe\n */" },
#endif
		{ "Elite.DisplayName", "\xe7\xb2\xbe\xe8\x8b\xb1\xe6\x80\xaa\xe7\x89\xa9" },
		{ "Elite.Name", "EEnemyType::Elite" },
		{ "MiniBoss.DisplayName", "\xe5\xb0\x8f""Boss" },
		{ "MiniBoss.Name", "EEnemyType::MiniBoss" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
		{ "Normal.DisplayName", "\xe6\x99\xae\xe9\x80\x9a\xe6\x80\xaa\xe7\x89\xa9" },
		{ "Normal.Name", "EEnemyType::Normal" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe7\xb1\xbb\xe5\x9e\x8b\xe6\x9e\x9a\xe4\xb8\xbe" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEnemyType::Normal", (int64)EEnemyType::Normal },
		{ "EEnemyType::Elite", (int64)EEnemyType::Elite },
		{ "EEnemyType::Boss", (int64)EEnemyType::Boss },
		{ "EEnemyType::MiniBoss", (int64)EEnemyType::MiniBoss },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	nullptr,
	"EEnemyType",
	"EEnemyType",
	Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AnabiosisOrigin_EEnemyType()
{
	if (!Z_Registration_Info_UEnum_EEnemyType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyType.InnerSingleton, Z_Construct_UEnum_AnabiosisOrigin_EEnemyType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEnemyType.InnerSingleton;
}
// End Enum EEnemyType

// Begin Enum EEnemyBehaviorType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEnemyBehaviorType;
static UEnum* EEnemyBehaviorType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEnemyBehaviorType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEnemyBehaviorType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("EEnemyBehaviorType"));
	}
	return Z_Registration_Info_UEnum_EEnemyBehaviorType.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EEnemyBehaviorType>()
{
	return EEnemyBehaviorType_StaticEnum();
}
struct Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Aggressive.DisplayName", "\xe4\xb8\xbb\xe5\x8a\xa8" },
		{ "Aggressive.Name", "EEnemyBehaviorType::Aggressive" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe8\xa1\x8c\xe4\xb8\xba\xe6\xa8\xa1\xe5\xbc\x8f\xe6\x9e\x9a\xe4\xb8\xbe\n */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
		{ "Passive.DisplayName", "\xe8\xa2\xab\xe5\x8a\xa8" },
		{ "Passive.Name", "EEnemyBehaviorType::Passive" },
		{ "Patrol.DisplayName", "\xe5\xb7\xa1\xe9\x80\xbb" },
		{ "Patrol.Name", "EEnemyBehaviorType::Patrol" },
		{ "Territorial.DisplayName", "\xe9\xa2\x86\xe5\x9c\xb0" },
		{ "Territorial.Name", "EEnemyBehaviorType::Territorial" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\x8c\xe4\xb8\xba\xe6\xa8\xa1\xe5\xbc\x8f\xe6\x9e\x9a\xe4\xb8\xbe" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEnemyBehaviorType::Passive", (int64)EEnemyBehaviorType::Passive },
		{ "EEnemyBehaviorType::Aggressive", (int64)EEnemyBehaviorType::Aggressive },
		{ "EEnemyBehaviorType::Territorial", (int64)EEnemyBehaviorType::Territorial },
		{ "EEnemyBehaviorType::Patrol", (int64)EEnemyBehaviorType::Patrol },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	nullptr,
	"EEnemyBehaviorType",
	"EEnemyBehaviorType",
	Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType()
{
	if (!Z_Registration_Info_UEnum_EEnemyBehaviorType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEnemyBehaviorType.InnerSingleton, Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEnemyBehaviorType.InnerSingleton;
}
// End Enum EEnemyBehaviorType

// Begin ScriptStruct FEnemyAttributeData
static_assert(std::is_polymorphic<FEnemyAttributeData>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FEnemyAttributeData cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EnemyAttributeData;
class UScriptStruct* FEnemyAttributeData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EnemyAttributeData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EnemyAttributeData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEnemyAttributeData, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("EnemyAttributeData"));
	}
	return Z_Registration_Info_UScriptStruct_EnemyAttributeData.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UScriptStruct* StaticStruct<FEnemyAttributeData>()
{
	return FEnemyAttributeData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FEnemyAttributeData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\x95\x8c\xe4\xba\xba\xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae\xe7\xbb\x93\xe6\x9e\x84\n */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x95\x8c\xe4\xba\xba\xe5\xb1\x9e\xe6\x80\xa7\xe6\x95\xb0\xe6\x8d\xae\xe7\xbb\x93\xe6\x9e\x84" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyType_MetaData[] = {
		{ "Category", "Basic" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x9f\xba\xe6\x9c\xac\xe4\xbf\xa1\xe6\x81\xaf */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe6\x9c\xac\xe4\xbf\xa1\xe6\x81\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BehaviorType_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Level_MetaData[] = {
		{ "Category", "Basic" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialHealth_MetaData[] = {
		{ "Category", "Combat" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x88\x98\xe6\x96\x97\xe5\xb1\x9e\xe6\x80\xa7 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x88\x98\xe6\x96\x97\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialMaxHealth_MetaData[] = {
		{ "Category", "Combat" },
		{ "ClampMin", "1.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackPower_MetaData[] = {
		{ "Category", "Combat" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Defense_MetaData[] = {
		{ "Category", "Combat" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetectionRange_MetaData[] = {
		{ "Category", "AI" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI\xe8\xa1\x8c\xe4\xb8\xba\xe5\x8f\x82\xe6\x95\xb0 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI\xe8\xa1\x8c\xe4\xb8\xba\xe5\x8f\x82\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PatrolRadius_MetaData[] = {
		{ "Category", "AI" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChaseRange_MetaData[] = {
		{ "Category", "AI" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AggroThreshold_MetaData[] = {
		{ "Category", "AI" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackRange_MetaData[] = {
		{ "Category", "Combat Behavior" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x88\x98\xe6\x96\x97\xe8\xa1\x8c\xe4\xb8\xba\xe5\x8f\x82\xe6\x95\xb0 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x88\x98\xe6\x96\x97\xe8\xa1\x8c\xe4\xb8\xba\xe5\x8f\x82\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackInterval_MetaData[] = {
		{ "Category", "Combat Behavior" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCanUseSpecialAttack_MetaData[] = {
		{ "Category", "Combat Behavior" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExperienceValue_MetaData[] = {
		{ "Category", "Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xa5\x96\xe5\x8a\xb1\xe7\xb3\xbb\xe7\xbb\x9f */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xa5\x96\xe5\x8a\xb1\xe7\xb3\xbb\xe7\xbb\x9f" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LootChance_MetaData[] = {
		{ "Category", "Rewards" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Data/EnemyAttributeData.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_EnemyType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EnemyType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_BehaviorType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_BehaviorType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Level;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialMaxHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackPower;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Defense;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DetectionRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PatrolRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChaseRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AggroThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackInterval;
	static void NewProp_bCanUseSpecialAttack_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCanUseSpecialAttack;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ExperienceValue;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LootChance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEnemyAttributeData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_EnemyType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_EnemyType = { "EnemyType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, EnemyType), Z_Construct_UEnum_AnabiosisOrigin_EEnemyType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyType_MetaData), NewProp_EnemyType_MetaData) }; // 3134939465
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_BehaviorType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_BehaviorType = { "BehaviorType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, BehaviorType), Z_Construct_UEnum_AnabiosisOrigin_EEnemyBehaviorType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BehaviorType_MetaData), NewProp_BehaviorType_MetaData) }; // 4275559113
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_Level = { "Level", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, Level), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Level_MetaData), NewProp_Level_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_InitialHealth = { "InitialHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, InitialHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialHealth_MetaData), NewProp_InitialHealth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_InitialMaxHealth = { "InitialMaxHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, InitialMaxHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialMaxHealth_MetaData), NewProp_InitialMaxHealth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackPower = { "AttackPower", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, AttackPower), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackPower_MetaData), NewProp_AttackPower_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_Defense = { "Defense", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, Defense), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Defense_MetaData), NewProp_Defense_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_DetectionRange = { "DetectionRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, DetectionRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetectionRange_MetaData), NewProp_DetectionRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_PatrolRadius = { "PatrolRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, PatrolRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PatrolRadius_MetaData), NewProp_PatrolRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_ChaseRange = { "ChaseRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, ChaseRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChaseRange_MetaData), NewProp_ChaseRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AggroThreshold = { "AggroThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, AggroThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AggroThreshold_MetaData), NewProp_AggroThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackRange = { "AttackRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, AttackRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackRange_MetaData), NewProp_AttackRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackInterval = { "AttackInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, AttackInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackInterval_MetaData), NewProp_AttackInterval_MetaData) };
void Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_bCanUseSpecialAttack_SetBit(void* Obj)
{
	((FEnemyAttributeData*)Obj)->bCanUseSpecialAttack = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_bCanUseSpecialAttack = { "bCanUseSpecialAttack", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FEnemyAttributeData), &Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_bCanUseSpecialAttack_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCanUseSpecialAttack_MetaData), NewProp_bCanUseSpecialAttack_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_ExperienceValue = { "ExperienceValue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, ExperienceValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExperienceValue_MetaData), NewProp_ExperienceValue_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_LootChance = { "LootChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnemyAttributeData, LootChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LootChance_MetaData), NewProp_LootChance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_EnemyType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_EnemyType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_BehaviorType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_BehaviorType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_Level,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_InitialHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_InitialMaxHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackPower,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_Defense,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_DetectionRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_PatrolRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_ChaseRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AggroThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_AttackInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_bCanUseSpecialAttack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_ExperienceValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewProp_LootChance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"EnemyAttributeData",
	Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::PropPointers),
	sizeof(FEnemyAttributeData),
	alignof(FEnemyAttributeData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEnemyAttributeData()
{
	if (!Z_Registration_Info_UScriptStruct_EnemyAttributeData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EnemyAttributeData.InnerSingleton, Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_EnemyAttributeData.InnerSingleton;
}
// End ScriptStruct FEnemyAttributeData

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EEnemyType_StaticEnum, TEXT("EEnemyType"), &Z_Registration_Info_UEnum_EEnemyType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3134939465U) },
		{ EEnemyBehaviorType_StaticEnum, TEXT("EEnemyBehaviorType"), &Z_Registration_Info_UEnum_EEnemyBehaviorType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4275559113U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEnemyAttributeData::StaticStruct, Z_Construct_UScriptStruct_FEnemyAttributeData_Statics::NewStructOps, TEXT("EnemyAttributeData"), &Z_Registration_Info_UScriptStruct_EnemyAttributeData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEnemyAttributeData), 2666615881U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_1817605941(TEXT("/Script/AnabiosisOrigin"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Data_EnemyAttributeData_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
