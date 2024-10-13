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
	
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

	FindSpawnPoints();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);
	GetWorld()->SpawnActor<AEnemy>(enmeyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));

	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	for (auto spawn : allActors)
	{
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if (spawn->GetName().Contains("BP_EnemySpawnPoint"))
		{
			//스폰 목록에 추가
			spawnPoints.Add(spawn);
		}
	}
}

