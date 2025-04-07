// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnabiosisOrigin/Public/AnabiosisOriginTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnabiosisOriginTypes() {}

// Begin Cross Module References
ANABIOSISORIGIN_API UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory();
UPackage* Z_Construct_UPackage__Script_AnabiosisOrigin();
// End Cross Module References

// Begin Enum EAnabiosisDebugCategory
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EAnabiosisDebugCategory;
static UEnum* EAnabiosisDebugCategory_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EAnabiosisDebugCategory.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EAnabiosisDebugCategory.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory, (UObject*)Z_Construct_UPackage__Script_AnabiosisOrigin(), TEXT("EAnabiosisDebugCategory"));
	}
	return Z_Registration_Info_UEnum_EAnabiosisDebugCategory.OuterSingleton;
}
template<> ANABIOSISORIGIN_API UEnum* StaticEnum<EAnabiosisDebugCategory>()
{
	return EAnabiosisDebugCategory_StaticEnum();
}
struct Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Abilities.Comment", "// \xe6\x9c\xaa\xe5\x88\x86\xe7\xb1\xbb\xe7\x9a\x84\xe8\xb0\x83\xe8\xaf\x95\xe4\xbf\xa1\xe6\x81\xaf\n" },
		{ "Abilities.DisplayName", "\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb3\xbb\xe7\xbb\x9f" },
		{ "Abilities.Name", "EAnabiosisDebugCategory::Abilities" },
		{ "Abilities.ToolTip", "\xe6\x9c\xaa\xe5\x88\x86\xe7\xb1\xbb\xe7\x9a\x84\xe8\xb0\x83\xe8\xaf\x95\xe4\xbf\xa1\xe6\x81\xaf" },
		{ "All.Comment", "// \xe7\x9b\xb8\xe6\x9c\xba\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95\n" },
		{ "All.DisplayName", "\xe5\x85\xa8\xe9\x83\xa8" },
		{ "All.Name", "EAnabiosisDebugCategory::All" },
		{ "All.ToolTip", "\xe7\x9b\xb8\xe6\x9c\xba\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95" },
		{ "BlueprintType", "true" },
		{ "Camera.Comment", "// \xe7\xa7\xbb\xe5\x8a\xa8\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95\n" },
		{ "Camera.DisplayName", "\xe7\x9b\xb8\xe6\x9c\xba\xe7\xb3\xbb\xe7\xbb\x9f" },
		{ "Camera.Name", "EAnabiosisDebugCategory::Camera" },
		{ "Camera.ToolTip", "\xe7\xa7\xbb\xe5\x8a\xa8\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95" },
		{ "Combat.Comment", "// \xe8\x83\xbd\xe5\x8a\x9b\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95\n" },
		{ "Combat.DisplayName", "\xe6\x88\x98\xe6\x96\x97\xe7\xb3\xbb\xe7\xbb\x9f" },
		{ "Combat.Name", "EAnabiosisDebugCategory::Combat" },
		{ "Combat.ToolTip", "\xe8\x83\xbd\xe5\x8a\x9b\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** \xe8\xb0\x83\xe8\xaf\x95\xe4\xbf\xa1\xe6\x81\xaf\xe5\x88\x86\xe7\xb1\xbb\xe6\x9e\x9a\xe4\xb8\xbe */" },
#endif
		{ "ModuleRelativePath", "AnabiosisOrigin/Public/AnabiosisOriginTypes.h" },
		{ "Movement.Comment", "// \xe6\x88\x98\xe6\x96\x97\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95\n" },
		{ "Movement.DisplayName", "\xe7\xa7\xbb\xe5\x8a\xa8\xe7\xb3\xbb\xe7\xbb\x9f" },
		{ "Movement.Name", "EAnabiosisDebugCategory::Movement" },
		{ "Movement.ToolTip", "\xe6\x88\x98\xe6\x96\x97\xe7\xb3\xbb\xe7\xbb\x9f\xe7\x9b\xb8\xe5\x85\xb3\xe8\xb0\x83\xe8\xaf\x95" },
		{ "None.DisplayName", "\xe6\x97\xa0" },
		{ "None.Name", "EAnabiosisDebugCategory::None" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xe8\xb0\x83\xe8\xaf\x95\xe4\xbf\xa1\xe6\x81\xaf\xe5\x88\x86\xe7\xb1\xbb\xe6\x9e\x9a\xe4\xb8\xbe" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EAnabiosisDebugCategory::None", (int64)EAnabiosisDebugCategory::None },
		{ "EAnabiosisDebugCategory::Abilities", (int64)EAnabiosisDebugCategory::Abilities },
		{ "EAnabiosisDebugCategory::Combat", (int64)EAnabiosisDebugCategory::Combat },
		{ "EAnabiosisDebugCategory::Movement", (int64)EAnabiosisDebugCategory::Movement },
		{ "EAnabiosisDebugCategory::Camera", (int64)EAnabiosisDebugCategory::Camera },
		{ "EAnabiosisDebugCategory::All", (int64)EAnabiosisDebugCategory::All },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AnabiosisOrigin,
	nullptr,
	"EAnabiosisDebugCategory",
	"EAnabiosisDebugCategory",
	Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory()
{
	if (!Z_Registration_Info_UEnum_EAnabiosisDebugCategory.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EAnabiosisDebugCategory.InnerSingleton, Z_Construct_UEnum_AnabiosisOrigin_EAnabiosisDebugCategory_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EAnabiosisDebugCategory.InnerSingleton;
}
// End Enum EAnabiosisDebugCategory

// Begin Registration
struct Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_AnabiosisOriginTypes_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EAnabiosisDebugCategory_StaticEnum, TEXT("EAnabiosisDebugCategory"), &Z_Registration_Info_UEnum_EAnabiosisDebugCategory, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3104903582U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_AnabiosisOriginTypes_h_3712355257(TEXT("/Script/AnabiosisOrigin"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_AnabiosisOriginTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AnabiosisOrigin_Source_AnabiosisOrigin_Public_AnabiosisOriginTypes_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
