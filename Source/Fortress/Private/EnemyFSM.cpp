// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "FTRPlayer.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAnim.h"


// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	auto Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AFTRPlayer::StaticClass());
	target = Cast<AFTRPlayer>(Actor);
	Me = Cast<AEnemy>(GetOwner());
	
	anim = Cast<UEnemyAnim>(Me->GetMesh()->GetAnimInstance());
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString LogMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, LogMsg);

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}

void UEnemyFSM::IdleState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > IdleDelayTime)
	{
		mState = EEnemyState::Move;
		CurrentTime = 0;
	}

	anim->animState = mState;
}

void UEnemyFSM::MoveState()
{
	// 타깃(플레이어) 방향으로 이동
	FVector Destination = target->GetActorLocation();
	FVector Dir = Destination - Me->GetActorLocation();
	Me->AddMovementInput(Dir.GetSafeNormal());

	// 공격 범위 들어오면 공격!
	if (Dir.Size() < AttackRange)
	{
		mState = EEnemyState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		CurrentTime = AttackDelayTime;
	}
}

void UEnemyFSM::AttackState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackDelayTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack!!!!"));
		CurrentTime = 0;
		anim->bAttackPlay = true;
	}

	// 타깃(플레이어)와 일정 이상 멀어지면 Move
	float Distance = FVector::Distance(target->GetActorLocation(), Me->GetActorLocation());
	if (Distance > AttackRange)
	{
		mState = EEnemyState::Move;
		anim->animState = mState;
	}
}

void UEnemyFSM::DamageState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > DamageDelayTime)
	{
		mState = EEnemyState::Idle;
		CurrentTime = 0;
		anim->animState = mState;
	}
}

void UEnemyFSM::DieState()
{
	FVector P0 = Me->GetActorLocation();
	FVector VT = FVector::DownVector * DieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + VT;
	Me->SetActorLocation(P);

	// 만약 2미터 이상 내려왔다면
	if (P.Z < -200.0f)
	{
		Me->Destroy();
	}
}

void UEnemyFSM::OnDamageProcess()
{
	//시험(플레이어 Input 함수에 구현되어 있어야 함)
	//Me->Destroy();

	HP--;
	if (HP > 0)
	{
		mState = EEnemyState::Damage;
	}
	else
	{
		mState = EEnemyState::Die;
		// 콜라이더 비활성화
		Me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	anim->animState = mState;
}

