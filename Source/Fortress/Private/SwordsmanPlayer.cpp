// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordsmanPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ASwordsmanPlayer::ASwordsmanPlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300;
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 80));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	bUseControllerRotationYaw = true;
	SpringArmComp->bUsePawnControlRotation = true;
	CameraComp->bUsePawnControlRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = 700;

	maxHp = 10;
	hp = maxHp;

	UE_LOG(LogTemp, Warning, TEXT("Player inint"));
}

void ASwordsmanPlayer::Attack()
{
	Super::Attack();

	// 라인 트레이스
	FVector startPos = CameraComp->GetComponentLocation();
	FVector endPos = CameraComp->GetComponentLocation() + CameraComp->GetForwardVector() * 700;

	FHitResult Hit;
	FCollisionQueryParams Params;
	// 플레이어를 충돌 판정에서 제외
	Params.AddIgnoredActor(this);

	// 충돌 정보, 시작 위치, 종료 위치, 검출 채널, 충돌 옵션
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, startPos, endPos, ECC_Visibility, Params);
	if (bHit)
	{
		// 충돌 위치에 효과 재생
		FTransform effectPos;
		effectPos.SetLocation(Hit.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), attackEffect, effectPos);

		Super::CheckEnemy(Hit);
	}
}