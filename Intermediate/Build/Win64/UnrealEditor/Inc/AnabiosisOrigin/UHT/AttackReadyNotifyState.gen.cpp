// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Animation/AttackReadyNotifyState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAttackReadyNotifyState() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAttackReadyNotifyState();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAttackReadyNotifyState_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimNotifyState();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UAttackReadyNotifyState
void UAttackReadyNotifyState::StaticRegisterNativesUAttackReadyNotifyState()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAttackReadyNotifyState);
UClass* Z_Construct_UClass_UAttackReadyNotifyState_NoRegister()
{
	return UAttackReadyNotifyState::StaticClass();
}
struct Z_Construct_UClass_UAttackReadyNotifyState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\x94\xbb\xe5\x87\xbb\xe5\x87\x86\xe5\xa4\x87\xe9\x80\x9a\xe7\x9f\xa5\xe7\x8a\xb6\xe6\x80\x81\xe7\xb1\xbb\n * \xe6\xa0\x87\xe8\xae\xb0\xe8\xa7\x92\xe8\x89\xb2\xe5\x8f\xaf\xe6\x8e\xa5\xe6\x94\xb6\xe8\xbf\x9e\xe5\x87\xbb\xe8\xbe\x93\xe5\x85\xa5\xe7\x9a\x84\xe9\x98\xb6\xe6\xae\xb5\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "AnabiosisOrigin/Public/Animation/AttackReadyNotifyState.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/AttackReadyNotifyState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x94\xbb\xe5\x87\xbb\xe5\x87\x86\xe5\xa4\x87\xe9\x80\x9a\xe7\x9f\xa5\xe7\x8a\xb6\xe6\x80\x81\xe7\xb1\xbb\n\xe6\xa0\x87\xe8\xae\xb0\xe8\xa7\x92\xe8\x89\xb2\xe5\x8f\xaf\xe6\x8e\xa5\xe6\x94\xb6\xe8\xbf\x9e\xe5\x87\xbb\xe8\xbe\x93\xe5\x85\xa5\xe7\x9a\x84\xe9\x98\xb6\xe6\xae\xb5" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAttackReadyNotifyState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAttackReadyNotifyState_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotifyState,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAttackReadyNotifyState_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAttackReadyNotifyState_Statics::ClassParams = {
	&UAttackReadyNotifyState::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001130A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAttackReadyNotifyState_Statics::Class_MetaDataParams), Z_Construct_UClass_UAttackReadyNotifyState_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAttackReadyNotifyState()
{
	if (!Z_Registration_Info_UClass_UAttackReadyNotifyState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAttackReadyNotifyState.OuterSingleton, Z_Construct_UClass_UAttackReadyNotifyState_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAttackReadyNotifyState.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UAttackReadyNotifyState>()
{
	return UAttackReadyNotifyState::StaticClass();
}
UAttackReadyNotifyState::UAttackReadyNotifyState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAttackReadyNotifyState);
UAttackReadyNotifyState::~UAttackReadyNotifyState() {}
// End Class UAttackReadyNotifyState

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackReadyNotifyState_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAttackReadyNotifyState, UAttackReadyNotifyState::StaticClass, TEXT("UAttackReadyNotifyState"), &Z_Registration_Info_UClass_UAttackReadyNotifyState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAttackReadyNotifyState), 3680234035U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackReadyNotifyState_h_3963025977(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackReadyNotifyState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackReadyNotifyState_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
