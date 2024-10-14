// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class FORTRESS_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    // 랜덤으로 미리 저장된 위치에서 적 생성
    // 스폰 간격
    UPROPERTY(EditAnywhere, Category = SpawnSetting)
    float MinTime = 5;
    UPROPERTY(EditAnywhere, Category = SpawnSetting)
    float MaxTime = 10;

    // 적 스폰 위치 정보 배열
    UPROPERTY(EditAnywhere, Category = SpawnSetting)
    TArray<class AActor*> SpawnPoints;
    // AEnemy 타입의 블루프린트 저장 변수
    UPROPERTY(EditAnywhere, Category = SpawnSetting)
    TSubclassOf<class AEnemy> EnemyFactory;

    // 스폰 타이머
    FTimerHandle SpawnTimerHandle;
    // 적 생성 함수
    void CreateEnemy();

    // 스폰할 위치를 찾아 동적 할당
    void FindSpawnPoints();
};
