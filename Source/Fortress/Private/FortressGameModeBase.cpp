// Fill out your copyright notice in the Description page of Project Settings.


#include "FortressGameModeBase.h"
#include "FTRPlayer.h"
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

AFortressGameModeBase::AFortressGameModeBase()
{
   // if(selectedCharaterClass != nullptr) 
}

void AFortressGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    DefaultPawnClass = Cast<USelectInstance>(GetGameInstance())->selectedCharaterClass;

    if (Cast<USelectInstance>(GetGameInstance())->bSelectArcher != true)
    {
        AController* cont = GetWorld()->GetFirstPlayerController();

        if (cont)
        {   
            AActor* startSpot = nullptr;
            TArray<AActor*> PlayerStarts;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

            if (PlayerStarts.Num() > 0)
            {
                startSpot = PlayerStarts[0];
            }

            APawn* curPawn = cont->GetPawn();
            if (curPawn)
            {
                // 현재 폰 제거
                curPawn->Destroy();
                UE_LOG(LogTemp, Warning, TEXT("pawn destroy"));
            }

            APawn* newPawn = SpawnDefaultPawnFor(cont, startSpot);
            if (newPawn)
            {
                cont->Possess(newPawn);

                APlayerController* pc = GetWorld()->GetFirstPlayerController();
                if (pc)
                {
                    pc->SetInputMode(FInputModeGameOnly());
                }
                cont->EnableInput(pc);

                if (cont->GetPawn() == newPawn)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Possession successful: %s"), *newPawn->GetName());
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Possession failed."));
                }
            }

            // GetWorld()->GetAuthGameMode()->RestartPlayer(cont);
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


