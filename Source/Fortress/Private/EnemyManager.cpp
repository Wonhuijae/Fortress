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

    // ���� ���� �ð�
    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    // ���� Ÿ�̸� ����
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyManager::CreateEnemy, CreateTime);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
    // ���� ��ġ ���ϱ�
    int index = FMath::RandRange(0, SpawnPoints.Num() - 1);
    // �� ���� �� ��ġ
    GetWorld()->SpawnActor<AEnemy>(EnemyFactory, SpawnPoints[index]->GetActorLocation(), FRotator(0));

    // �ٽ� ���� �ð��� CreateEnemy �Լ��� ȣ��ǵ��� Ÿ�̸� ����
    float CreateTime = FMath::RandRange(MinTime, MaxTime);
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemyManager::CreateEnemy, CreateTime);
}

void AEnemyManager::FindSpawnPoints()
{
    // �˻����� ã�� ����� ������ �迭
    TArray<AActor*> AllActors;
    // ���ϴ� Ÿ���� ���� ��� ã��
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
    // ã�� ����� ���� ��� �ݺ�������    
    for (auto Spawn : AllActors)
    {
        // ã�� ������ �̸��� �ش� ���ڿ��� �����ϰ� �ִٸ�
        if (Spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
        {
            // ���� ��Ͽ� �߰�
            SpawnPoints.Add(Spawn);
        }
    }
}