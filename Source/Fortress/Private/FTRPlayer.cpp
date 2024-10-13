// Fill out your copyright notice in the Description page of Project Settings.


#include "FTRPlayer.h"
#include "PlayerMove.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAnim.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFTRPlayer::AFTRPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void AFTRPlayer::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(IMC_TPS, 0);
		}
	}

}

// Called every frame
void AFTRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFTRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		playerMove->SetupInputBinding(PlayerInput);

		PlayerInput->BindAction(IA_Fire, ETriggerEvent::Started, this, &AFTRPlayer::InputFire);
	}
}

void AFTRPlayer::InputFire(const FInputActionValue& inputValue)
{
	auto anim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	anim->PlayAttackAnim();
	// UGameplayStatics::PlaySound2D(GetWorld(), attackSound);

	Attack();
}

void AFTRPlayer::CheckEnemy(FHitResult Hit)
{
	// 적인지 확인
	auto enemy = Hit.GetActor()->GetDefaultSubobjectByName(TEXT("EnemyFSM"));
	if (enemy)
	{

	}
}

void AFTRPlayer::OnHitEvent()
{
	hp--;
	if (hp <= 0)
	{
		OnGameOver();
	}
}

// BlueprintNativeEvent로 선언된 함수는 _Implementation을 붙여 구현함
void AFTRPlayer::OnGameOver_Implementation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

