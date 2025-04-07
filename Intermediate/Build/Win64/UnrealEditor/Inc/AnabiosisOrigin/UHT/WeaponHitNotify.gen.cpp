// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWeaponHitNotify() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UWeaponHitNotify();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UWeaponHitNotify_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UWeaponHitNotify
void UWeaponHitNotify::StaticRegisterNativesUWeaponHitNotify()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UWeaponHitNotify);
UClass* Z_Construct_UClass_UWeaponHitNotify_NoRegister()
{
	return UWeaponHitNotify::StaticClass();
}
struct Z_Construct_UClass_UWeaponHitNotify_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe6\xad\xa6\xe5\x99\xa8\xe5\x91\xbd\xe4\xb8\xad\xe6\xa3\x80\xe6\xb5\x8b\xe9\x80\x9a\xe7\x9f\xa5\n * \xe4\xbd\xbf\xe7\x94\xa8\xe6\xad\xa6\xe5\x99\xa8\xe6\x8f\x92\xe6\xa7\xbd\xe7\x9a\x84\xe8\xb5\xb7\xe7\x82\xb9\xe5\x92\x8c\xe7\xbb\x88\xe7\x82\xb9\xe6\x89\xa7\xe8\xa1\x8c\xe7\xb2\xbe\xe7\xa1\xae\xe7\x9a\x84\xe5\xb0\x84\xe7\xba\xbf\xe6\xa3\x80\xe6\xb5\x8b\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xad\xa6\xe5\x99\xa8\xe5\x91\xbd\xe4\xb8\xad\xe6\xa3\x80\xe6\xb5\x8b\xe9\x80\x9a\xe7\x9f\xa5\n\xe4\xbd\xbf\xe7\x94\xa8\xe6\xad\xa6\xe5\x99\xa8\xe6\x8f\x92\xe6\xa7\xbd\xe7\x9a\x84\xe8\xb5\xb7\xe7\x82\xb9\xe5\x92\x8c\xe7\xbb\x88\xe7\x82\xb9\xe6\x89\xa7\xe8\xa1\x8c\xe7\xb2\xbe\xe7\xa1\xae\xe7\x9a\x84\xe5\xb0\x84\xe7\xba\xbf\xe6\xa3\x80\xe6\xb5\x8b" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeaponStartSocketName_MetaData[] = {
		{ "Category", "WeaponHit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xad\xa6\xe5\x99\xa8\xe5\xb0\x84\xe7\xba\xbf\xe8\xb5\xb7\xe7\x82\xb9\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc/\xe6\x8f\x92\xe6\xa7\xbd\xe5\x90\x8d\xe7\xa7\xb0 (\xe4\xbe\x8b\xe5\xa6\x82 \"weapon_start\" \xe6\x88\x96 \"blade_base\") */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xad\xa6\xe5\x99\xa8\xe5\xb0\x84\xe7\xba\xbf\xe8\xb5\xb7\xe7\x82\xb9\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc/\xe6\x8f\x92\xe6\xa7\xbd\xe5\x90\x8d\xe7\xa7\xb0 (\xe4\xbe\x8b\xe5\xa6\x82 \"weapon_start\" \xe6\x88\x96 \"blade_base\")" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeaponEndSocketName_MetaData[] = {
		{ "Category", "WeaponHit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\xad\xa6\xe5\x99\xa8\xe5\xb0\x84\xe7\xba\xbf\xe7\xbb\x88\xe7\x82\xb9\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc/\xe6\x8f\x92\xe6\xa7\xbd\xe5\x90\x8d\xe7\xa7\xb0 (\xe4\xbe\x8b\xe5\xa6\x82 \"weapon_end\" \xe6\x88\x96 \"blade_tip\") */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\xad\xa6\xe5\x99\xa8\xe5\xb0\x84\xe7\xba\xbf\xe7\xbb\x88\xe7\x82\xb9\xe7\x9a\x84\xe9\xaa\xa8\xe9\xaa\xbc/\xe6\x8f\x92\xe6\xa7\xbd\xe5\x90\x8d\xe7\xa7\xb0 (\xe4\xbe\x8b\xe5\xa6\x82 \"weapon_end\" \xe6\x88\x96 \"blade_tip\")" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TraceRadius_MetaData[] = {
		{ "Category", "WeaponHit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xb0\x84\xe7\xba\xbf\xe6\xa3\x80\xe6\xb5\x8b\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88""0\xe4\xb8\xba\xe7\xba\xbf\xe5\xbd\xa2\xe6\xa3\x80\xe6\xb5\x8b\xef\xbc\x8c>0\xe4\xb8\xba\xe7\x90\x83\xe5\xbd\xa2\xe6\xa3\x80\xe6\xb5\x8b\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb0\x84\xe7\xba\xbf\xe6\xa3\x80\xe6\xb5\x8b\xe5\x8d\x8a\xe5\xbe\x84\xef\xbc\x88""0\xe4\xb8\xba\xe7\xba\xbf\xe5\xbd\xa2\xe6\xa3\x80\xe6\xb5\x8b\xef\xbc\x8c>0\xe4\xb8\xba\xe7\x90\x83\xe5\xbd\xa2\xe6\xa3\x80\xe6\xb5\x8b\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDebugTrace_MetaData[] = {
		{ "Category", "WeaponHit|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xb0\x83\xe8\xaf\x95\xe6\xa8\xa1\xe5\xbc\x8f\xef\xbc\x88\xe6\x98\xaf\xe5\x90\xa6\xe6\x98\xbe\xe7\xa4\xba\xe5\xb0\x84\xe7\xba\xbf\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb0\x83\xe8\xaf\x95\xe6\xa8\xa1\xe5\xbc\x8f\xef\xbc\x88\xe6\x98\xaf\xe5\x90\xa6\xe6\x98\xbe\xe7\xa4\xba\xe5\xb0\x84\xe7\xba\xbf\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DebugDisplayTime_MetaData[] = {
		{ "Category", "WeaponHit|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x91\xbd\xe4\xb8\xad\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xba\xe6\x97\xb6\xe9\x95\xbf\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x91\xbd\xe4\xb8\xad\xe4\xbf\xa1\xe6\x81\xaf\xe6\x98\xbe\xe7\xa4\xba\xe6\x97\xb6\xe9\x95\xbf\xef\xbc\x88\xe7\xa7\x92\xef\xbc\x89" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bApplyDamage_MetaData[] = {
		{ "Category", "WeaponHit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x98\xaf\xe5\x90\xa6\xe5\xba\x94\xe7\x94\xa8\xe4\xbc\xa4\xe5\xae\xb3 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x98\xaf\xe5\x90\xa6\xe5\xba\x94\xe7\x94\xa8\xe4\xbc\xa4\xe5\xae\xb3" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseDamage_MetaData[] = {
		{ "Category", "WeaponHit" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x9f\xba\xe7\xa1\x80\xe4\xbc\xa4\xe5\xae\xb3\xe5\x80\xbc */" },
#endif
		{ "EditCondition", "bApplyDamage" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Animation/WeaponHitNotify.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe4\xbc\xa4\xe5\xae\xb3\xe5\x80\xbc" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_WeaponStartSocketName;
	static const UECodeGen_Private::FNamePropertyParams NewProp_WeaponEndSocketName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TraceRadius;
	static void NewProp_bDebugTrace_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDebugTrace;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DebugDisplayTime;
	static void NewProp_bApplyDamage_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bApplyDamage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseDamage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UWeaponHitNotify>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_WeaponStartSocketName = { "WeaponStartSocketName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWeaponHitNotify, WeaponStartSocketName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeaponStartSocketName_MetaData), NewProp_WeaponStartSocketName_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_WeaponEndSocketName = { "WeaponEndSocketName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWeaponHitNotify, WeaponEndSocketName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeaponEndSocketName_MetaData), NewProp_WeaponEndSocketName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_TraceRadius = { "TraceRadius", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWeaponHitNotify, TraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TraceRadius_MetaData), NewProp_TraceRadius_MetaData) };
void Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bDebugTrace_SetBit(void* Obj)
{
	((UWeaponHitNotify*)Obj)->bDebugTrace = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bDebugTrace = { "bDebugTrace", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UWeaponHitNotify), &Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bDebugTrace_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDebugTrace_MetaData), NewProp_bDebugTrace_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_DebugDisplayTime = { "DebugDisplayTime", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWeaponHitNotify, DebugDisplayTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DebugDisplayTime_MetaData), NewProp_DebugDisplayTime_MetaData) };
void Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bApplyDamage_SetBit(void* Obj)
{
	((UWeaponHitNotify*)Obj)->bApplyDamage = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bApplyDamage = { "bApplyDamage", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UWeaponHitNotify), &Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bApplyDamage_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bApplyDamage_MetaData), NewProp_bApplyDamage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_BaseDamage = { "BaseDamage", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UWeaponHitNotify, BaseDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseDamage_MetaData), NewProp_BaseDamage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UWeaponHitNotify_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_WeaponStartSocketName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_WeaponEndSocketName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_TraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bDebugTrace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_DebugDisplayTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_bApplyDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UWeaponHitNotify_Statics::NewProp_BaseDamage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWeaponHitNotify_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UWeaponHitNotify_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimNotify,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UWeaponHitNotify_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UWeaponHitNotify_Statics::ClassParams = {
	&UWeaponHitNotify::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UWeaponHitNotify_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UWeaponHitNotify_Statics::PropPointers),
	0,
	0x001120A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UWeaponHitNotify_Statics::Class_MetaDataParams), Z_Construct_UClass_UWeaponHitNotify_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UWeaponHitNotify()
{
	if (!Z_Registration_Info_UClass_UWeaponHitNotify.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UWeaponHitNotify.OuterSingleton, Z_Construct_UClass_UWeaponHitNotify_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UWeaponHitNotify.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UWeaponHitNotify>()
{
	return UWeaponHitNotify::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UWeaponHitNotify);
UWeaponHitNotify::~UWeaponHitNotify() {}
// End Class UWeaponHitNotify

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_WeaponHitNotify_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UWeaponHitNotify, UWeaponHitNotify::StaticClass, TEXT("UWeaponHitNotify"), &Z_Registration_Info_UClass_UWeaponHitNotify, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UWeaponHitNotify), 2910984306U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_WeaponHitNotify_h_2879616851(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_WeaponHitNotify_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Animation_WeaponHitNotify_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
