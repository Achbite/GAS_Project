// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Abilities/BaseAttack.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseAttack() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UBaseAttack();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UBaseAttack_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilityTask_PlayMontageAndWait_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UBaseAttack Function HandleMontageBlendOut
struct Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8a\xa8\xe7\x94\xbb\xe6\xb7\xb7\xe5\x90\x88\xe7\xbb\x93\xe6\x9d\x9f\xe5\x9b\x9e\xe8\xb0\x83 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa8\xe7\x94\xbb\xe6\xb7\xb7\xe5\x90\x88\xe7\xbb\x93\xe6\x9d\x9f\xe5\x9b\x9e\xe8\xb0\x83" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAttack, nullptr, "HandleMontageBlendOut", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBaseAttack::execHandleMontageBlendOut)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMontageBlendOut();
	P_NATIVE_END;
}
// End Class UBaseAttack Function HandleMontageBlendOut

// Begin Class UBaseAttack Function HandleMontageCancelled
struct Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8a\xa8\xe7\x94\xbb\xe5\x8f\x96\xe6\xb6\x88\xe5\x9b\x9e\xe8\xb0\x83 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa8\xe7\x94\xbb\xe5\x8f\x96\xe6\xb6\x88\xe5\x9b\x9e\xe8\xb0\x83" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAttack, nullptr, "HandleMontageCancelled", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBaseAttack::execHandleMontageCancelled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMontageCancelled();
	P_NATIVE_END;
}
// End Class UBaseAttack Function HandleMontageCancelled

// Begin Class UBaseAttack Function HandleMontageCompleted
struct Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8a\xa8\xe7\x94\xbb\xe5\xae\x8c\xe6\x88\x90\xe5\x9b\x9e\xe8\xb0\x83 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa8\xe7\x94\xbb\xe5\xae\x8c\xe6\x88\x90\xe5\x9b\x9e\xe8\xb0\x83" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAttack, nullptr, "HandleMontageCompleted", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBaseAttack::execHandleMontageCompleted)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMontageCompleted();
	P_NATIVE_END;
}
// End Class UBaseAttack Function HandleMontageCompleted

// Begin Class UBaseAttack Function HandleMontageInterrupted
struct Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe5\x8a\xa8\xe7\x94\xbb\xe8\xa2\xab\xe6\x89\x93\xe6\x96\xad\xe5\x9b\x9e\xe8\xb0\x83 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x8a\xa8\xe7\x94\xbb\xe8\xa2\xab\xe6\x89\x93\xe6\x96\xad\xe5\x9b\x9e\xe8\xb0\x83" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseAttack, nullptr, "HandleMontageInterrupted", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBaseAttack::execHandleMontageInterrupted)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleMontageInterrupted();
	P_NATIVE_END;
}
// End Class UBaseAttack Function HandleMontageInterrupted

// Begin Class UBaseAttack
void UBaseAttack::StaticRegisterNativesUBaseAttack()
{
	UClass* Class = UBaseAttack::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "HandleMontageBlendOut", &UBaseAttack::execHandleMontageBlendOut },
		{ "HandleMontageCancelled", &UBaseAttack::execHandleMontageCancelled },
		{ "HandleMontageCompleted", &UBaseAttack::execHandleMontageCompleted },
		{ "HandleMontageInterrupted", &UBaseAttack::execHandleMontageInterrupted },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseAttack);
UClass* Z_Construct_UClass_UBaseAttack_NoRegister()
{
	return UBaseAttack::StaticClass();
}
struct Z_Construct_UClass_UBaseAttack_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb1\xbb\n * \xe8\xb4\x9f\xe8\xb4\xa3\xe5\xae\x9e\xe7\x8e\xb0\xe8\xa7\x92\xe8\x89\xb2\xe7\x9a\x84\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe8\xa1\x8c\xe4\xb8\xba\xef\xbc\x8c\xe5\x8c\x85\xe6\x8b\xac\xe5\x8a\xa8\xe7\x94\xbb\xe6\x92\xad\xe6\x94\xbe\xe5\x92\x8c\xe7\xbd\x91\xe7\xbb\x9c\xe5\x90\x8c\xe6\xad\xa5\n */" },
#endif
		{ "IncludePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb1\xbb\n\xe8\xb4\x9f\xe8\xb4\xa3\xe5\xae\x9e\xe7\x8e\xb0\xe8\xa7\x92\xe8\x89\xb2\xe7\x9a\x84\xe5\x9f\xba\xe7\xa1\x80\xe6\x94\xbb\xe5\x87\xbb\xe8\xa1\x8c\xe4\xb8\xba\xef\xbc\x8c\xe5\x8c\x85\xe6\x8b\xac\xe5\x8a\xa8\xe7\x94\xbb\xe6\x92\xad\xe6\x94\xbe\xe5\x92\x8c\xe7\xbd\x91\xe7\xbb\x9c\xe5\x90\x8c\xe6\xad\xa5" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackMontage_MetaData[] = {
		{ "Category", "\xe8\x83\xbd\xe5\x8a\x9b" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\xa8\xe7\x94\xbb\xe8\xb5\x84\xe6\xba\x90 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe6\x94\xbb\xe5\x87\xbb\xe5\x8a\xa8\xe7\x94\xbb\xe8\xb5\x84\xe6\xba\x90" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AbilityTag_MetaData[] = {
		{ "Category", "\xe8\x83\xbd\xe5\x8a\x9b" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\x83\xbd\xe5\x8a\x9b\xe6\xa0\x87\xe7\xad\xbe" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MontageTask_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe7\xae\xa1\xe7\x90\x86\xe5\x8a\xa8\xe7\x94\xbb\xe6\x92\xad\xe6\x94\xbe\xe7\x9a\x84\xe4\xbb\xbb\xe5\x8a\xa1 */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Abilities/BaseAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe7\xae\xa1\xe7\x90\x86\xe5\x8a\xa8\xe7\x94\xbb\xe6\x92\xad\xe6\x94\xbe\xe7\x9a\x84\xe4\xbb\xbb\xe5\x8a\xa1" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackMontage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AbilityTag;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MontageTask;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBaseAttack_HandleMontageBlendOut, "HandleMontageBlendOut" }, // 3773409759
		{ &Z_Construct_UFunction_UBaseAttack_HandleMontageCancelled, "HandleMontageCancelled" }, // 4056962242
		{ &Z_Construct_UFunction_UBaseAttack_HandleMontageCompleted, "HandleMontageCompleted" }, // 2306949747
		{ &Z_Construct_UFunction_UBaseAttack_HandleMontageInterrupted, "HandleMontageInterrupted" }, // 3771345291
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseAttack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBaseAttack_Statics::NewProp_AttackMontage = { "AttackMontage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAttack, AttackMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackMontage_MetaData), NewProp_AttackMontage_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseAttack_Statics::NewProp_AbilityTag = { "AbilityTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAttack, AbilityTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AbilityTag_MetaData), NewProp_AbilityTag_MetaData) }; // 1298103297
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBaseAttack_Statics::NewProp_MontageTask = { "MontageTask", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBaseAttack, MontageTask), Z_Construct_UClass_UAbilityTask_PlayMontageAndWait_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MontageTask_MetaData), NewProp_MontageTask_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseAttack_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAttack_Statics::NewProp_AttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAttack_Statics::NewProp_AbilityTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseAttack_Statics::NewProp_MontageTask,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAttack_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBaseAttack_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameplayAbility,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAttack_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseAttack_Statics::ClassParams = {
	&UBaseAttack::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBaseAttack_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAttack_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseAttack_Statics::Class_MetaDataParams), Z_Construct_UClass_UBaseAttack_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBaseAttack()
{
	if (!Z_Registration_Info_UClass_UBaseAttack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBaseAttack.OuterSingleton, Z_Construct_UClass_UBaseAttack_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBaseAttack.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UBaseAttack>()
{
	return UBaseAttack::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseAttack);
UBaseAttack::~UBaseAttack() {}
// End Class UBaseAttack

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBaseAttack, UBaseAttack::StaticClass, TEXT("UBaseAttack"), &Z_Registration_Info_UClass_UBaseAttack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseAttack), 2998274519U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_1551250603(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Abilities_BaseAttack_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
