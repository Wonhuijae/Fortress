// Fill out your copyright notice in the Description page of Project Settings.


#include "FortressGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerStart.h"
#include "SelectInstance.h"
#include "Kismet/GameplayStatics.h"

//APawn* AFortressGameModeBase::SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot)
//{
//    USelectInstance* gameIns = Cast<USelectInstance>(GetGameInstance());
//
//    if (selectedCharaterClass)
//    {
//        UClass* spawnClass = gameIns->selectedCharaterClass;
//
//        if (spawnClass)
//        {
//            ACharacter* newChar = GetWorld()->SpawnActor<ACharacter>(spawnClass, StartSpot->GetTransform());
//            if (newChar)
//            {
//                NewPlayer->Possess(newChar);
//                return newChar;
//            }
//        }
//    }
//
//    return Super::SpawnDefaultPawnFor(NewPlayer, StartSpot);
//}

void AFortressGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    DefaultPawnClass = Cast<USelectInstance>(GetGameInstance())->selectedCharaterClass;

    if (Cast<USelectInstance>(GetGameInstance())->bSelectArcher != true)
    {
        AController* cont = GetWorld()->GetFirstPlayerController();

        if (cont)
        {
            APawn* curPawn = cont->GetPawn();
            if (curPawn)
            {
                // 현재 폰 제거
                curPawn->Destroy();
                UE_LOG(LogTemp, Warning, TEXT("pawn destroy"));
            }

            GetWorld()->GetAuthGameMode()->RestartPlayer(cont);
            //UE_LOG(LogTemp, Warning, TEXT("New Pawn: %s"), *newPawn->GetName());
            UE_LOG(LogTemp, Warning, TEXT("New Pawn: %s"), *cont->GetPawn()->GetName());
        }
    }
}

void AFortressGameModeBase::SetClass(bool _select)
{
    Cast<USelectInstance>(GetGameInstance())->bSelectArcher = _select;
    Cast<USelectInstance>(GetGameInstance())->selectedCharaterClass = selectedCharaterClass;
}


