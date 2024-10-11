// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "FTRPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player == nullptr)
	{
		auto Owner = TryGetPawnOwner();
		Player = Cast<AFTRPlayer>(Owner);
	}
	
	if( Player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is null"));
		return;
	}

	FVector Forward = Player->GetActorForwardVector();
	FVector Velocity = Player->GetVelocity();
	Speed = FVector::DotProduct(Forward, Velocity);

	FVector Right = Player->GetActorRightVector();
	Direction = FVector::DotProduct(Right, Velocity);

	UCharacterMovementComponent* Movement = Player->GetCharacterMovement();
	bIsInAir = Movement->IsFalling();
}

void UPlayerAnim::PlayAttackAnim()
{
	Montage_Play(AttackAnimMontage);
}
