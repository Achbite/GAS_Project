/*
 * Copyright (C) 2025 [Wang]
 * ... (License comments) ...
 */

/*
* 文件名: DamageInterface.h
* 功能描述： 定义伤害接口 IDamageInterface。
*            提供一个标准化的方式来处理 Actor 受到的伤害。
* 结构：
* - 继承自 UInterface。
* - 定义一个纯虚函数 HandleDamage，需要在实现类中重写。
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

// 接口类，不能直接实例化
UINTERFACE(MinimalAPI, Blueprintable) // Blueprintable 允许蓝图实现此接口
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief 伤害处理接口。
 *        任何希望能够以特定方式处理伤害的 Actor 都应实现此接口。
 */
class ANABIOSISORIGIN_API IDamageInterface
{
	GENERATED_BODY()

public:
	/**
	 * @brief 处理接收到的伤害。
	 * @param DamageAmount 伤害量。
	 * @param DamageEvent 伤害事件详情。
	 * @param EventInstigator 造成伤害的控制器。
	 * @param DamageCauser 造成伤害的 Actor。
	 * @return 实际应用的伤害量。
	 *
	 * @note 这是接口函数，需要在实现类中提供具体逻辑。
	 *       可以使用 BlueprintNativeEvent 或 BlueprintImplementableEvent 使其在蓝图中可实现。
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Damage")
	float HandleDamage(float DamageAmount, const struct FDamageEvent& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
};
