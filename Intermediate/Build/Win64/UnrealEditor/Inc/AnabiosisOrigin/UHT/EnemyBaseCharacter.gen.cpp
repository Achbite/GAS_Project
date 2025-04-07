// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyBaseCharacter() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AEnemyBaseCharacter();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AEnemyBaseCharacter_NoRegister();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UEnemyAttributeSet_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemInterface_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class AEnemyBaseCharacter
void AEnemyBaseCharacter::StaticRegisterNativesAEnemyBaseCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyBaseCharacter);
UClass* Z_Construct_UClass_AEnemyBaseCharacter_NoRegister()
{
	return AEnemyBaseCharacter::StaticClass();
}
struct Z_Construct_UClass_AEnemyBaseCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbilitySystemComponent_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** GAS\xe7\xb3\xbb\xe7\xbb\x9f\xe7\xbb\x84\xe4\xbb\xb6 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "GAS\xe7\xb3\xbb\xe7\xbb\x9f\xe7\xbb\x84\xe4\xbb\xb6" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttributeSet_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xb1\x9e\xe6\x80\xa7\xe9\x9b\x86 */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb1\x9e\xe6\x80\xa7\xe9\x9b\x86" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultAbilities_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe9\xbb\x98\xe8\xae\xa4\xe8\x83\xbd\xe5\x8a\x9b\xe5\x88\x97\xe8\xa1\xa8 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe9\xbb\x98\xe8\xae\xa4\xe8\x83\xbd\xe5\x8a\x9b\xe5\x88\x97\xe8\xa1\xa8" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultEffects_MetaData[] = {
		{ "Category", "Abilities" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x88\x9d\xe5\xa7\x8b\xe5\x8c\x96\xe6\x97\xb6\xe8\xb5\x8b\xe4\xba\x88\xe7\x9a\x84\xe6\x95\x88\xe6\x9e\x9c */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Characters/EnemyBaseCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x88\x9d\xe5\xa7\x8b\xe5\x8c\x96\xe6\x97\xb6\xe8\xb5\x8b\xe4\xba\x88\xe7\x9a\x84\xe6\x95\x88\xe6\x9e\x9c" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AbilitySystemComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttributeSet;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DefaultAbilities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultAbilities;
	static const UECodeGen_Private::FClassPropertyParams NewProp_DefaultEffects_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultEffects;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyBaseCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBaseCharacter, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbilitySystemComponent_MetaData), NewProp_AbilitySystemComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_AttributeSet = { "AttributeSet", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBaseCharacter, AttributeSet), Z_Construct_UClass_UEnemyAttributeSet_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttributeSet_MetaData), NewProp_AttributeSet_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultAbilities_Inner = { "DefaultAbilities", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_UGameplayAbility_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultAbilities = { "DefaultAbilities", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBaseCharacter, DefaultAbilities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultAbilities_MetaData), NewProp_DefaultAbilities_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultEffects_Inner = { "DefaultEffects", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_UGameplayEffect_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultEffects = { "DefaultEffects", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyBaseCharacter, DefaultEffects), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultEffects_MetaData), NewProp_DefaultEffects_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyBaseCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_AbilitySystemComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_AttributeSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultAbilities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultAbilities,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultEffects_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyBaseCharacter_Statics::NewProp_DefaultEffects,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBaseCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AEnemyBaseCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBaseCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UAbilitySystemInterface_NoRegister, (int32)VTABLE_OFFSET(AEnemyBaseCharacter, IAbilitySystemInterface), false },  // 2272790346
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyBaseCharacter_Statics::ClassParams = {
	&AEnemyBaseCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AEnemyBaseCharacter_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBaseCharacter_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBaseCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyBaseCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyBaseCharacter()
{
	if (!Z_Registration_Info_UClass_AEnemyBaseCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyBaseCharacter.OuterSingleton, Z_Construct_UClass_AEnemyBaseCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyBaseCharacter.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<AEnemyBaseCharacter>()
{
	return AEnemyBaseCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyBaseCharacter);
AEnemyBaseCharacter::~AEnemyBaseCharacter() {}
// End Class AEnemyBaseCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyBaseCharacter, AEnemyBaseCharacter::StaticClass, TEXT("AEnemyBaseCharacter"), &Z_Registration_Info_UClass_AEnemyBaseCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyBaseCharacter), 410008591U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_3339280682(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Characters_EnemyBaseCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
