// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SelectInstance.generated.h"

/**
 * 
 */
UCLASS()
class FORTRESS_API USelectInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UClass* selectedCharaterClass;

	bool bSelectArcher = true;
};
