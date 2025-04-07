// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisOriginGameMode() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisOriginGameMode();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_AAnabiosisOriginGameMode_NoRegister();
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class AAnabiosisOriginGameMode Function IsDebugCategoryEnabled
struct Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics
{
	struct AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms
	{
		EAnabiosisDebugCategory Category;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "\xe8\xb0\x83\xe8\xaf\x95" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\x8e\xb7\xe5\x8f\x96\xe6\x8c\x87\xe5\xae\x9a\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe7\x94\xa8 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x8e\xb7\xe5\x8f\x96\xe6\x8c\x87\xe5\xae\x9a\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe6\x98\xaf\xe5\x90\xa6\xe5\x90\xaf\xe7\x94\xa8" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms, Category), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory, METADATA_PARAMS(0, nullptr) }; // 3104903582
void Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms), &Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginGameMode, nullptr, "IsDebugCategoryEnabled", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::AnabiosisOriginGameMode_eventIsDebugCategoryEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginGameMode::execIsDebugCategoryEnabled)
{
	P_GET_ENUM(EAnabiosisDebugCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsDebugCategoryEnabled(EAnabiosisDebugCategory(Z_Param_Category));
	P_NATIVE_END;
}
// End Class AAnabiosisOriginGameMode Function IsDebugCategoryEnabled

// Begin Class AAnabiosisOriginGameMode Function SetDebugCategoryEnabled
struct Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics
{
	struct AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms
	{
		EAnabiosisDebugCategory Category;
		bool bEnabled;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "\xe8\xb0\x83\xe8\xaf\x95" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xae\xbe\xe7\xbd\xae\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe7\x9a\x84\xe5\x90\xaf\xe7\x94\xa8\xe7\x8a\xb6\xe6\x80\x81 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xae\xbe\xe7\xbd\xae\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe7\x9a\x84\xe5\x90\xaf\xe7\x94\xa8\xe7\x8a\xb6\xe6\x80\x81" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static void NewProp_bEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms, Category), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory, METADATA_PARAMS(0, nullptr) }; // 3104903582
void Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_bEnabled_SetBit(void* Obj)
{
	((AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms*)Obj)->bEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms), &Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_bEnabled_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::NewProp_bEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAnabiosisOriginGameMode, nullptr, "SetDebugCategoryEnabled", nullptr, nullptr, Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::PropPointers), sizeof(Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::AnabiosisOriginGameMode_eventSetDebugCategoryEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAnabiosisOriginGameMode::execSetDebugCategoryEnabled)
{
	P_GET_ENUM(EAnabiosisDebugCategory,Z_Param_Category);
	P_GET_UBOOL(Z_Param_bEnabled);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDebugCategoryEnabled(EAnabiosisDebugCategory(Z_Param_Category),Z_Param_bEnabled);
	P_NATIVE_END;
}
// End Class AAnabiosisOriginGameMode Function SetDebugCategoryEnabled

// Begin Class AAnabiosisOriginGameMode
void AAnabiosisOriginGameMode::StaticRegisterNativesAAnabiosisOriginGameMode()
{
	UClass* Class = AAnabiosisOriginGameMode::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "IsDebugCategoryEnabled", &AAnabiosisOriginGameMode::execIsDebugCategoryEnabled },
		{ "SetDebugCategoryEnabled", &AAnabiosisOriginGameMode::execSetDebugCategoryEnabled },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAnabiosisOriginGameMode);
UClass* Z_Construct_UClass_AAnabiosisOriginGameMode_NoRegister()
{
	return AAnabiosisOriginGameMode::StaticClass();
}
struct Z_Construct_UClass_AAnabiosisOriginGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnabledDebugCategories_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\xb7\xb2\xe5\x90\xaf\xe7\x94\xa8\xe7\x9a\x84\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe9\x9b\x86\xe5\x90\x88 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/GameFramework/AnabiosisOriginGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\xb7\xb2\xe5\x90\xaf\xe7\x94\xa8\xe7\x9a\x84\xe8\xb0\x83\xe8\xaf\x95\xe7\xb1\xbb\xe5\x88\xab\xe9\x9b\x86\xe5\x90\x88" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_EnabledDebugCategories_ElementProp_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EnabledDebugCategories_ElementProp;
	static const UECodeGen_Private::FSetPropertyParams NewProp_EnabledDebugCategories;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AAnabiosisOriginGameMode_IsDebugCategoryEnabled, "IsDebugCategoryEnabled" }, // 1643838898
		{ &Z_Construct_UFunction_AAnabiosisOriginGameMode_SetDebugCategoryEnabled, "SetDebugCategoryEnabled" }, // 1524618174
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAnabiosisOriginGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories_ElementProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories_ElementProp = { "EnabledDebugCategories", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory, METADATA_PARAMS(0, nullptr) }; // 3104903582
const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories = { "EnabledDebugCategories", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAnabiosisOriginGameMode, EnabledDebugCategories), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnabledDebugCategories_MetaData), NewProp_EnabledDebugCategories_MetaData) }; // 3104903582
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories_ElementProp_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories_ElementProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::NewProp_EnabledDebugCategories,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::ClassParams = {
	&AAnabiosisOriginGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::PropPointers),
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAnabiosisOriginGameMode()
{
	if (!Z_Registration_Info_UClass_AAnabiosisOriginGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAnabiosisOriginGameMode.OuterSingleton, Z_Construct_UClass_AAnabiosisOriginGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAnabiosisOriginGameMode.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<AAnabiosisOriginGameMode>()
{
	return AAnabiosisOriginGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAnabiosisOriginGameMode);
AAnabiosisOriginGameMode::~AAnabiosisOriginGameMode() {}
// End Class AAnabiosisOriginGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAnabiosisOriginGameMode, AAnabiosisOriginGameMode::StaticClass, TEXT("AAnabiosisOriginGameMode"), &Z_Registration_Info_UClass_AAnabiosisOriginGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAnabiosisOriginGameMode), 72895850U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_3142138487(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_GameFramework_AnabiosisOriginGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
