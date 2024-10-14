// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
    FindSpawnPoints();

    // 랜덤 생성 시간
    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    // 스폰 타이머 설정
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyManager::CreateEnemy, CreateTime);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
    // 랜덤 위치 구하기
    int index = FMath::RandRange(0, SpawnPoints.Num() - 1);
    // 적 생성 및 배치
    GetWorld()->SpawnActor<AEnemy>(EnemyFactory, SpawnPoints[index]->GetActorLocation(), FRotator(0));

    // 다시 랜덤 시간에 CreateEnemy 함수가 호출되도록 타이머 설정
    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyManager::CreateEnemy, CreateTime);
}

void AEnemyManager::FindSpawnPoints()
{
    // 검색으로 찾은 결과를 저장할 배열
    TArray<AActor*> AllActors;
    // 원하는 타입의 액터 모두 찾기
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
    // 찾는 결과가 있을 경우 반복적으로    
    for (auto Spawn : AllActors)
    {
        // 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
        if (Spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
        {
            // 스폰 목록에 추가
            SpawnPoints.Add(Spawn);
        }
    }
}