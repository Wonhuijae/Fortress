// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.9f));
	}

	EnemyFSM = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));

	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/ABP_Enemy.ABP_Enemy_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HPComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComp"));
	HPComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UUserWidget> tempHP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_EnemyHP.WBP_EnemyHP'"));
	if (tempHP.Succeeded())
	{
		HPComp->SetWidgetClass(tempHP.Class);
		HPComp->SetDrawSize(FVector2D(150, 20));
		HPComp->SetRelativeLocation(FVector(0, 0, 90));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UCapsuleComponent* Cap = GetCapsuleComponent();
	auto EMesh = GetMesh();
	Cap->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Cap->SetCollisionResponseToChannel
	(ECC_Camera, ECR_Ignore);

	EMesh->SetCollisionResponseToChannel
	(ECC_Visibility, ECR_Ignore);
	EMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyFSM->InitHp();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = HPComp->K2_GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);

	HPComp->SetWorldRotation(NewRotation);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

