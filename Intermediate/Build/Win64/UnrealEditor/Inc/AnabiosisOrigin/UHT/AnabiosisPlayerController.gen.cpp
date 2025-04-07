// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisPlayerController() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisOriginCharacter_NoRegister();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisPlayerController();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisPlayerController_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class AAnabiosisPlayerController
void AAnabiosisPlayerController::StaticRegisterNativesAAnabiosisPlayerController()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAnabiosisPlayerController);
UClass* Z_Construct_UClass_AAnabiosisPlayerController_NoRegister()
{
	return AAnabiosisPlayerController::StaticClass();
}
struct Z_Construct_UClass_AAnabiosisPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe8\xbe\x93\xe5\x85\xa5\xe6\x98\xa0\xe5\xb0\x84\xe4\xb8\x8a\xe4\xb8\x8b\xe6\x96\x87\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xbe\x93\xe5\x85\xa5\xe6\x98\xa0\xe5\xb0\x84\xe4\xb8\x8a\xe4\xb8\x8b\xe6\x96\x87" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9f\xba\xe7\xa1\x80\xe8\xbe\x93\xe5\x85\xa5\xe5\x8a\xa8\xe4\xbd\x9c\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe8\xbe\x93\xe5\x85\xa5\xe5\x8a\xa8\xe4\xbd\x9c" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackAction_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5|\xe6\x88\x98\xe6\x96\x97" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe6\x88\x98\xe6\x96\x97\xe7\x9b\xb8\xe5\x85\xb3\xe8\xbe\x93\xe5\x85\xa5\xe5\x8a\xa8\xe4\xbd\x9c\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x88\x98\xe6\x96\x97\xe7\x9b\xb8\xe5\x85\xb3\xe8\xbe\x93\xe5\x85\xa5\xe5\x8a\xa8\xe4\xbd\x9c" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackLookAction_MetaData[] = {
		{ "Category", "\xe8\xbe\x93\xe5\x85\xa5|\xe6\x88\x98\xe6\x96\x97" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NormalCameraArmLength_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe8\xae\xbe\xe7\xbd\xae\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe8\xae\xbe\xe7\xbd\xae" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CombatCameraArmLength_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CombatCameraOffset_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseMovementSpeed_MetaData[] = {
		{ "Category", "Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xa7\xbb\xe5\x8a\xa8\xe7\x9b\xb8\xe5\x85\xb3\xe5\x8f\x82\xe6\x95\xb0 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xa7\xbb\xe5\x8a\xa8\xe7\x9b\xb8\xe5\x85\xb3\xe5\x8f\x82\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SprintSpeedMultiplier_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseTurnRate_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xa7\x86\xe8\xa7\x92\xe7\x9b\xb8\xe5\x85\xb3\xe5\x8f\x82\xe6\x95\xb0 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xa7\x86\xe8\xa7\x92\xe7\x9b\xb8\xe5\x85\xb3\xe5\x8f\x82\xe6\x95\xb0" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseLookUpRate_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ControlledCharacter_MetaData[] = {
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Controllers/AnabiosisPlayerController.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackLookAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NormalCameraArmLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CombatCameraArmLength;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CombatCameraOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseMovementSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SprintSpeedMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseTurnRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseLookUpRate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ControlledCharacter;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAnabiosisPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_AttackAction = { "AttackAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, AttackAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackAction_MetaData), NewProp_AttackAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_AttackLookAction = { "AttackLookAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, AttackLookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackLookAction_MetaData), NewProp_AttackLookAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_NormalCameraArmLength = { "NormalCameraArmLength", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, NormalCameraArmLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NormalCameraArmLength_MetaData), NewProp_NormalCameraArmLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_CombatCameraArmLength = { "CombatCameraArmLength", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, CombatCameraArmLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CombatCameraArmLength_MetaData), NewProp_CombatCameraArmLength_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_CombatCameraOffset = { "CombatCameraOffset", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, CombatCameraOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CombatCameraOffset_MetaData), NewProp_CombatCameraOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseMovementSpeed = { "BaseMovementSpeed", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, BaseMovementSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseMovementSpeed_MetaData), NewProp_BaseMovementSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_SprintSpeedMultiplier = { "SprintSpeedMultiplier", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, SprintSpeedMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SprintSpeedMultiplier_MetaData), NewProp_SprintSpeedMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseTurnRate = { "BaseTurnRate", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, BaseTurnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseTurnRate_MetaData), NewProp_BaseTurnRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseLookUpRate = { "BaseLookUpRate", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, BaseLookUpRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseLookUpRate_MetaData), NewProp_BaseLookUpRate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_ControlledCharacter = { "ControlledCharacter", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisPlayerController, ControlledCharacter), Z_Construct_UClass_AAnabiosisOriginCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ControlledCharacter_MetaData), NewProp_ControlledCharacter_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAnabiosisPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_AttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_AttackLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_NormalCameraArmLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_CombatCameraArmLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_CombatCameraOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseMovementSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_SprintSpeedMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseTurnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_BaseLookUpRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisPlayerController_Statics::NewProp_ControlledCharacter,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AAnabiosisPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAnabiosisPlayerController_Statics::ClassParams = {
	&AAnabiosisPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AAnabiosisPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisPlayerController_Statics::PropPointers),
	0,
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AAnabiosisPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAnabiosisPlayerController()
{
	if (!Z_Registration_Info_UClass_AAnabiosisPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAnabiosisPlayerController.OuterSingleton, Z_Construct_UClass_AAnabiosisPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAnabiosisPlayerController.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<AAnabiosisPlayerController>()
{
	return AAnabiosisPlayerController::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAnabiosisPlayerController);
AAnabiosisPlayerController::~AAnabiosisPlayerController() {}
// End Class AAnabiosisPlayerController

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Controllers_AnabiosisPlayerController_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAnabiosisPlayerController, AAnabiosisPlayerController::StaticClass, TEXT("AAnabiosisPlayerController"), &Z_Registration_Info_UClass_AAnabiosisPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAnabiosisPlayerController), 288513269U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Controllers_AnabiosisPlayerController_h_1447618508(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Controllers_AnabiosisPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Controllers_AnabiosisPlayerController_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
