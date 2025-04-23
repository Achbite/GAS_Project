/*
 * Copyright (C) 2025 [Wang]
 * ... (Copyleft header) ...
 */

/*
* 文件名: WeaponBase.cpp
* 功能描述： 实现武器 Actor 基类的功能。
*/

#include "Items/WeaponBase.h"
#include "Components/StaticMeshComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false; // 通常武器本身不需要 Tick

	// 创建静态网格体组件
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh; // 将网格体设为根组件

	// 默认禁用碰撞，由使用者（角色）处理交互
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}
