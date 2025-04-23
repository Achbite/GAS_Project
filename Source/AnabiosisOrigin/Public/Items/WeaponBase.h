/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: WeaponBase.h
* 功能描述： 定义武器 Actor 的基类。包含武器的静态网格体组件。
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UStaticMeshComponent;

UCLASS(Blueprintable, BlueprintType) // Allow Blueprint subclasses
class ANABIOSISORIGIN_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

protected:
	/** 武器的静态网格体组件 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

public:
	/** 获取武器网格体组件 */
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
};
