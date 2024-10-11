// Fill out your copyright notice in the Description page of Project Settings.


#include "FTRPlayer.h"
#include "PlayerMove.h"
#include "EnhancedInputComponent.h"

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
	}
}

void AFTRPlayer::Attack()
{
	
}

