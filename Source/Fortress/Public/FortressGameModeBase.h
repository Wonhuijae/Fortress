// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FortressGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FORTRESS_API AFortressGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFortressGameModeBase();

	//virtual APawn* SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot) override;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	UClass* selectedCharaterClass;

	UFUNCTION(BlueprintCallable)
	void SetClass(bool _select);
};
