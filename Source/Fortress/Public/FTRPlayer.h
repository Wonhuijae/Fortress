// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FTRPlayer.generated.h"

UCLASS()
class FORTRESS_API AFTRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFTRPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();

	// 스프링암
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	// 카메라(3인칭)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	// 속도
	UPROPERTY(EditAnywhere, Category = Move)
	float walkSpeed;
	
	UPROPERTY(EditAnywhere, Category = Move)
	float runSpeed;

	// 이동 함수

	// 점프 여부
	UPROPERTY(EditAnywhere, Category = Move)
	bool bInAir = false;
	
	// 체력

	// 공격력

	// 공격 함수

	// 이동 컴포넌트

	// 공격 컴포넌트
};
