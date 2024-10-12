// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class FORTRESS_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	class AFTRPlayer* Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	bool bIsInAir;

	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* AttackAnimMontage;

	void PlayAttackAnim();

	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* SelectAnimMontage;

	void PlaySelectAnim();
};
