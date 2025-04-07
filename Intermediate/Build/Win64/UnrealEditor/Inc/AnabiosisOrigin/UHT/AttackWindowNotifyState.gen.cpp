// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Animation/AttackWindowNotifyState.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAttackWindowNotifyState() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAttackWindowNotifyState();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UAttackWindowNotifyState_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimNotifyState();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UAttackWindowNotifyState
void UAttackWindowNotifyState::StaticRegisterNativesUAttackWindowNotifyState()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAttackWindowNotifyState);
UClass* Z_Construct_UClass_UAttackWindowNotifyState_NoRegister()
{
	return UAttackWindowNotifyState::StaticClass();
}
struct Z_Construct_UClass_UAttackWindowNotifyState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\x94\xbb\xe5\x87\xbb\xe7\xaa\x97\xe5\x8f\xa3\xe9\x80\x9a\xe7\x9f\xa5\xe7\x8a\xb6\xe6\x80\x81\xe7\xb1\xbb\n * \xe5\xae\x9a\xe4\xb9\x89\xe8\xa7\x92\xe8\x89\xb2\xe5\x8f\xaf\xe4\xbb\xa5\xe6\x8e\xa5\xe6\x94\xb6\xe8\xbf\x9e\xe5\x87\xbb\xe8\xbe\x93\xe5\x85\xa5\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4\xe7\xaa\x97\xe5\x8f\xa3\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "AnabiosisOrigin/Public/Animation/AttackWindowNotifyState.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/AttackWindowNotifyState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x94\xbb\xe5\x87\xbb\xe7\xaa\x97\xe5\x8f\xa3\xe9\x80\x9a\xe7\x9f\xa5\xe7\x8a\xb6\xe6\x80\x81\xe7\xb1\xbb\n\xe5\xae\x9a\xe4\xb9\x89\xe8\xa7\x92\xe8\x89\xb2\xe5\x8f\xaf\xe4\xbb\xa5\xe6\x8e\xa5\xe6\x94\xb6\xe8\xbf\x9e\xe5\x87\xbb\xe8\xbe\x93\xe5\x85\xa5\xe7\x9a\x84\xe6\x97\xb6\xe9\x97\xb4\xe7\xaa\x97\xe5\x8f\xa3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentAttackTag_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xbd\x93\xe5\x89\x8d\xe6\x94\xbb\xe5\x87\xbb\xe6\xa0\x87\xe7\xad\xbe\xef\xbc\x8c\xe8\xbf\x9e\xe5\x87\xbb\xe7\xaa\x97\xe5\x8f\xa3\xe6\x9c\x9f\xe9\x97\xb4\xe4\xbd\xbf\xe7\x94\xa8\xe6\xad\xa4\xe6\xa0\x87\xe7\xad\xbe\xe8\xaf\x86\xe5\x88\xab\xe4\xb8\x8b\xe4\xb8\x80\xe6\xac\xa1\xe6\x94\xbb\xe5\x87\xbb */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/AttackWindowNotifyState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xbd\x93\xe5\x89\x8d\xe6\x94\xbb\xe5\x87\xbb\xe6\xa0\x87\xe7\xad\xbe\xef\xbc\x8c\xe8\xbf\x9e\xe5\x87\xbb\xe7\xaa\x97\xe5\x8f\xa3\xe6\x9c\x9f\xe9\x97\xb4\xe4\xbd\xbf\xe7\x94\xa8\xe6\xad\xa4\xe6\xa0\x87\xe7\xad\xbe\xe8\xaf\x86\xe5\x88\xab\xe4\xb8\x8b\xe4\xb8\x80\xe6\xac\xa1\xe6\x94\xbb\xe5\x87\xbb" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseAttackTag_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe6\xa0\x87\xe7\xad\xbe\xef\xbc\x8c\xe7\xaa\x97\xe5\x8f\xa3\xe7\xbb\x93\xe6\x9d\x9f\xe6\x97\xb6\xe8\xbf\x98\xe5\x8e\x9f */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/AttackWindowNotifyState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe6\xa0\x87\xe7\xad\xbe\xef\xbc\x8c\xe7\xaa\x97\xe5\x8f\xa3\xe7\xbb\x93\xe6\x9d\x9f\xe6\x97\xb6\xe8\xbf\x98\xe5\x8e\x9f" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentAttackTag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BaseAttackTag;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAttackWindowNotifyState>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAttackWindowNotifyState_Statics::NewProp_CurrentAttackTag = { "CurrentAttackTag", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAttackWindowNotifyState, CurrentAttackTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentAttackTag_MetaData), NewProp_CurrentAttackTag_MetaData) }; // 1298103297
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAttackWindowNotifyState_Statics::NewProp_BaseAttackTag = { "BaseAttackTag", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAttackWindowNotifyState, BaseAttackTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseAttackTag_MetaData), NewProp_BaseAttackTag_MetaData) }; // 1298103297
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAttackWindowNotifyState_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAttackWindowNotifyState_Statics::NewProp_CurrentAttackTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAttackWindowNotifyState_Statics::NewProp_BaseAttackTag,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAttackWindowNotifyState_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAttackWindowNotifyState_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotifyState,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAttackWindowNotifyState_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAttackWindowNotifyState_Statics::ClassParams = {
	&UAttackWindowNotifyState::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UAttackWindowNotifyState_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UAttackWindowNotifyState_Statics::PropPointers),
	0,
	0x001130A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAttackWindowNotifyState_Statics::Class_MetaDataParams), Z_Construct_UClass_UAttackWindowNotifyState_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAttackWindowNotifyState()
{
	if (!Z_Registration_Info_UClass_UAttackWindowNotifyState.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAttackWindowNotifyState.OuterSingleton, Z_Construct_UClass_UAttackWindowNotifyState_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAttackWindowNotifyState.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UAttackWindowNotifyState>()
{
	return UAttackWindowNotifyState::StaticClass();
}
UAttackWindowNotifyState::UAttackWindowNotifyState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAttackWindowNotifyState);
UAttackWindowNotifyState::~UAttackWindowNotifyState() {}
// End Class UAttackWindowNotifyState

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackWindowNotifyState_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAttackWindowNotifyState, UAttackWindowNotifyState::StaticClass, TEXT("UAttackWindowNotifyState"), &Z_Registration_Info_UClass_UAttackWindowNotifyState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAttackWindowNotifyState), 2677662191U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackWindowNotifyState_h_3574696734(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackWindowNotifyState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_AttackWindowNotifyState_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
