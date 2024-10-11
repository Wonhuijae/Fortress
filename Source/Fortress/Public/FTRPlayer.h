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

	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	// ī�޶�(3��Ī)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	// InputMappingContext 변수
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_TPS;

	// �̵� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerMove;

	// ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerAttack;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 maxHp;

	UFUNCTION(BlueprintCallable, Category = Health)
	void OnHitEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health)
	void OnGameOver();
};
