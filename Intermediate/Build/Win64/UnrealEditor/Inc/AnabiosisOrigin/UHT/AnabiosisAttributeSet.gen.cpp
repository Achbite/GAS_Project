// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h"
#include "GameplayAbilities/Public/AttributeSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisAttributeSet() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAnabiosisAttributeSet();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAnabiosisAttributeSet_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAttributeSet();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UAnabiosisAttributeSet
void UAnabiosisAttributeSet::StaticRegisterNativesUAnabiosisAttributeSet()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAnabiosisAttributeSet);
UClass* Z_Construct_UClass_UAnabiosisAttributeSet_NoRegister()
{
	return UAnabiosisAttributeSet::StaticClass();
}
struct Z_Construct_UClass_UAnabiosisAttributeSet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Strength_MetaData[] = {
		{ "Category", "Attributes|Base" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Agility_MetaData[] = {
		{ "Category", "Attributes|Base" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Constitution_MetaData[] = {
		{ "Category", "Attributes|Base" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackPower_MetaData[] = {
		{ "Category", "Attributes|Derived" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xa1\x8d\xe7\x94\x9f\xe5\xb1\x9e\xe6\x80\xa7\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa1\x8d\xe7\x94\x9f\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementSpeed_MetaData[] = {
		{ "Category", "Attributes|Derived" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[] = {
		{ "Category", "Attributes|Status" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x8a\xb6\xe6\x80\x81\xe5\xb1\x9e\xe6\x80\xa7\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x8a\xb6\xe6\x80\x81\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Attributes|Status" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/AnabiosisAttributeSet.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Strength;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Agility;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Constitution;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AttackPower;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MovementSpeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Health;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnabiosisAttributeSet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Strength = { "Strength", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, Strength), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Strength_MetaData), NewProp_Strength_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Agility = { "Agility", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, Agility), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Agility_MetaData), NewProp_Agility_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Constitution = { "Constitution", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, Constitution), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Constitution_MetaData), NewProp_Constitution_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_AttackPower = { "AttackPower", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, AttackPower), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackPower_MetaData), NewProp_AttackPower_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_MovementSpeed = { "MovementSpeed", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, MovementSpeed), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementSpeed_MetaData), NewProp_MovementSpeed_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, Health), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Health_MetaData), NewProp_Health_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAnabiosisAttributeSet, MaxHealth), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHealth_MetaData), NewProp_MaxHealth_MetaData) }; // 675369593
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnabiosisAttributeSet_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Strength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Agility,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Constitution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_AttackPower,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_MovementSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_Health,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnabiosisAttributeSet_Statics::NewProp_MaxHealth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnabiosisAttributeSet_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAnabiosisAttributeSet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAttributeSet,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnabiosisAttributeSet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnabiosisAttributeSet_Statics::ClassParams = {
	&UAnabiosisAttributeSet::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAnabiosisAttributeSet_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAnabiosisAttributeSet_Statics::PropPointers),
	0,
	0x003000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnabiosisAttributeSet_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnabiosisAttributeSet_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAnabiosisAttributeSet()
{
	if (!Z_Registration_Info_UClass_UAnabiosisAttributeSet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnabiosisAttributeSet.OuterSingleton, Z_Construct_UClass_UAnabiosisAttributeSet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnabiosisAttributeSet.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UAnabiosisAttributeSet>()
{
	return UAnabiosisAttributeSet::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAnabiosisAttributeSet);
UAnabiosisAttributeSet::~UAnabiosisAttributeSet() {}
// End Class UAnabiosisAttributeSet

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_AnabiosisAttributeSet_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnabiosisAttributeSet, UAnabiosisAttributeSet::StaticClass, TEXT("UAnabiosisAttributeSet"), &Z_Registration_Info_UClass_UAnabiosisAttributeSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnabiosisAttributeSet), 3457120498U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_AnabiosisAttributeSet_h_1875902419(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_AnabiosisAttributeSet_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_AnabiosisAttributeSet_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
