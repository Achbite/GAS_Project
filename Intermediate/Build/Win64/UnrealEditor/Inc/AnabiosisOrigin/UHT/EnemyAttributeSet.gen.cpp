// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h"
#include "GameplayAbilities/Public/AttributeSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyAttributeSet() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UEnemyAttributeSet();
ANABIOSISORIGIN_API UClass* Z_Construct_UClass_UEnemyAttributeSet_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAttributeSet();
GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Class UEnemyAttributeSet Function InitializeFromDataTable
struct Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics
{
	struct EnemyAttributeSet_eventInitializeFromDataTable_Parms
	{
		const UDataTable* DataTable;
		FName RowName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "\xe5\xb1\x9e\xe6\x80\xa7" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe4\xbb\x8e\xe6\x95\xb0\xe6\x8d\xae\xe8\xa1\xa8\xe5\x88\x9d\xe5\xa7\x8b\xe5\x8c\x96\xe5\xb1\x9e\xe6\x80\xa7\xe5\x80\xbc */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe4\xbb\x8e\xe6\x95\xb0\xe6\x8d\xae\xe8\xa1\xa8\xe5\x88\x9d\xe5\xa7\x8b\xe5\x8c\x96\xe5\xb1\x9e\xe6\x80\xa7\xe5\x80\xbc" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DataTable_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RowName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DataTable;
	static const UECodeGen_Private::FNamePropertyParams NewProp_RowName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::NewProp_DataTable = { "DataTable", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAttributeSet_eventInitializeFromDataTable_Parms, DataTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DataTable_MetaData), NewProp_DataTable_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::NewProp_RowName = { "RowName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnemyAttributeSet_eventInitializeFromDataTable_Parms, RowName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RowName_MetaData), NewProp_RowName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::NewProp_DataTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::NewProp_RowName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEnemyAttributeSet, nullptr, "InitializeFromDataTable", nullptr, nullptr, Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::EnemyAttributeSet_eventInitializeFromDataTable_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::EnemyAttributeSet_eventInitializeFromDataTable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEnemyAttributeSet::execInitializeFromDataTable)
{
	P_GET_OBJECT(UDataTable,Z_Param_DataTable);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_RowName);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->InitializeFromDataTable(Z_Param_DataTable,Z_Param_Out_RowName);
	P_NATIVE_END;
}
// End Class UEnemyAttributeSet Function InitializeFromDataTable

// Begin Class UEnemyAttributeSet
void UEnemyAttributeSet::StaticRegisterNativesUEnemyAttributeSet()
{
	UClass* Class = UEnemyAttributeSet::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "InitializeFromDataTable", &UEnemyAttributeSet::execInitializeFromDataTable },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UEnemyAttributeSet);
UClass* Z_Construct_UClass_UEnemyAttributeSet_NoRegister()
{
	return UEnemyAttributeSet::StaticClass();
}
struct Z_Construct_UClass_UEnemyAttributeSet_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[] = {
		{ "Category", "Attributes|Base" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe5\x9f\xba\xe7\xa1\x80\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Attributes|Base" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackPower_MetaData[] = {
		{ "Category", "Attributes|Combat" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Defense_MetaData[] = {
		{ "Category", "Attributes|Combat" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetectionRange_MetaData[] = {
		{ "Category", "Attributes|AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// AI\xe7\x9b\xb8\xe5\x85\xb3\xe5\xb1\x9e\xe6\x80\xa7\n" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI\xe7\x9b\xb8\xe5\x85\xb3\xe5\xb1\x9e\xe6\x80\xa7" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AggroValue_MetaData[] = {
		{ "Category", "Attributes|AI" },
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/Attributes/EnemyAttributeSet.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Health;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AttackPower;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Defense;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DetectionRange;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AggroValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEnemyAttributeSet_InitializeFromDataTable, "InitializeFromDataTable" }, // 719046912
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnemyAttributeSet>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_Health = { "Health", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, Health), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Health_MetaData), NewProp_Health_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, MaxHealth), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHealth_MetaData), NewProp_MaxHealth_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_AttackPower = { "AttackPower", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, AttackPower), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackPower_MetaData), NewProp_AttackPower_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_Defense = { "Defense", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, Defense), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Defense_MetaData), NewProp_Defense_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_DetectionRange = { "DetectionRange", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, DetectionRange), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetectionRange_MetaData), NewProp_DetectionRange_MetaData) }; // 675369593
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_AggroValue = { "AggroValue", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnemyAttributeSet, AggroValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AggroValue_MetaData), NewProp_AggroValue_MetaData) }; // 675369593
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEnemyAttributeSet_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_Health,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_MaxHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_AttackPower,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_Defense,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_DetectionRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnemyAttributeSet_Statics::NewProp_AggroValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyAttributeSet_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UEnemyAttributeSet_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAttributeSet,
	(UObject* (*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyAttributeSet_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEnemyAttributeSet_Statics::ClassParams = {
	&UEnemyAttributeSet::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEnemyAttributeSet_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyAttributeSet_Statics::PropPointers),
	0,
	0x003000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEnemyAttributeSet_Statics::Class_MetaDataParams), Z_Construct_UClass_UEnemyAttributeSet_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UEnemyAttributeSet()
{
	if (!Z_Registration_Info_UClass_UEnemyAttributeSet.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEnemyAttributeSet.OuterSingleton, Z_Construct_UClass_UEnemyAttributeSet_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEnemyAttributeSet.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UClass* StaticClass<UEnemyAttributeSet>()
{
	return UEnemyAttributeSet::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UEnemyAttributeSet);
UEnemyAttributeSet::~UEnemyAttributeSet() {}
// End Class UEnemyAttributeSet

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_EnemyAttributeSet_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEnemyAttributeSet, UEnemyAttributeSet::StaticClass, TEXT("UEnemyAttributeSet"), &Z_Registration_Info_UClass_UEnemyAttributeSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEnemyAttributeSet), 1083177233U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_EnemyAttributeSet_h_155512564(TEXT("/Script/AnabiosisOrigin"),
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_EnemyAttributeSet_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_Attributes_EnemyAttributeSet_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
