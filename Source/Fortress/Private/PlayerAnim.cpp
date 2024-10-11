// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "ArcheryPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AArcheryPlayer>(ownerPawn);
}
