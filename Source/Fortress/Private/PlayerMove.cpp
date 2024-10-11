// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "ArcheryPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void UPlayerMove::BeginPlay()
{
    Super::BeginPlay();
    if(moveComp) moveComp->MaxWalkSpeed = walkSpeed;
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("moveComp is nullPtr"));
    }
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    PlayerMove();
}

void UPlayerMove::SetupInputBinding(class UEnhancedInputComponent* PlayerInput)
{
	// 바인딩 처리 함수
    PlayerInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &UPlayerMove::Turn);
    PlayerInput->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &UPlayerMove::LookUp);
    PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UPlayerMove::Move);

    PlayerInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMove::InputJump);

    // 뛰기 애니메이션
    PlayerInput->BindAction(IA_Run, ETriggerEvent::Started, this, &UPlayerMove::InputRun);
    PlayerInput->BindAction(IA_Run, ETriggerEvent::Completed, this, &UPlayerMove::InputRun);
}

void UPlayerMove::Turn(const FInputActionValue& inputValue)
{
    float value = inputValue.Get<float>();
    me->AddControllerYawInput(value);
}

void UPlayerMove::LookUp(const FInputActionValue& inputValue)
{
    float value = inputValue.Get<float>();
    me->AddControllerYawInput(value);
}

void UPlayerMove::Move(const FInputActionValue& inputValue)
{
    FVector2D value = inputValue.Get<FVector2D>();
    // 상하 입력 처리
    Direction.X = value.X;
    // 좌우 입력 처리
    Direction.Y = value.Y;
}

void UPlayerMove::PlayerMove()
{
    Direction = FTransform(me->GetControlRotation()).TransformVector(Direction);

    me->AddMovementInput(Direction);
    Direction = FVector::ZeroVector;
}

void UPlayerMove::InputJump(const FInputActionValue& inputValue)
{
    me->Jump();
}

void UPlayerMove::InputRun(const FInputActionValue& inputValue)
{
    auto Movement = me->GetCharacterMovement();
    // 만약, 현재 달리기 모드라면
    if (Movement->MaxWalkSpeed > walkSpeed)
    {
        // 걷기 속도로 전환
        Movement->MaxWalkSpeed = walkSpeed;
    }
    else
    {
        Movement->MaxWalkSpeed = runSpeed;
    }
}
