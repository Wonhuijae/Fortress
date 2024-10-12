// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTRPlayer.h"
#include "SwordsmanPlayer.generated.h"

/**
 * 
 */
UCLASS()
class FORTRESS_API ASwordsmanPlayer : public AFTRPlayer
{
	GENERATED_BODY()

public:
	ASwordsmanPlayer();

	virtual void Attack() override;
};
