// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class FORTRESS_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	UPlayerMove();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Turn;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_LookUp;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* IA_Run;

	void Turn(const struct  FInputActionValue& inputValue);

	void LookUp(const struct  FInputActionValue& inputValue);

	void Move(const struct  FInputActionValue& inputValue);

	void PlayerMove();

	void InputJump(const struct  FInputActionValue& inputValue);

	void InputRun(const struct  FInputActionValue& inputValue);

	// �̵� ����
	FVector Direction;

	// �ӵ�
	UPROPERTY(EditAnywhere, Category = Move)
	float walkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Move)
	float runSpeed = 600.f;

	// ���� ����
	UPROPERTY(EditAnywhere, Category = Move)
	bool bInAir = false;
};
