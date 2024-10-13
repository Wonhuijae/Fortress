// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "ArcheryPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

UPlayerMove::UPlayerMove()
{
    PrimaryComponentTick.bCanEverTick = true;
}

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
	// ���ε� ó�� �Լ�
    PlayerInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &UPlayerMove::Turn);
    PlayerInput->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &UPlayerMove::LookUp);
    PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UPlayerMove::Move);

    PlayerInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &UPlayerMove::InputJump);

    // �ٱ� �ִϸ��̼�
    PlayerInput->BindAction(IA_Run, ETriggerEvent::Started, this, &UPlayerMove::InputRun);
    PlayerInput->BindAction(IA_Run, ETriggerEvent::Completed, this, &UPlayerMove::InputRun);
    UE_LOG(LogTemp, Warning, TEXT("Controller bind: %s"), *(GetOwner()->GetName()));
}

void UPlayerMove::Turn(const FInputActionValue& inputValue)
{
    float value = inputValue.Get<float>();
    me->AddControllerYawInput(value);
}

void UPlayerMove::LookUp(const FInputActionValue& inputValue)
{
    float value = inputValue.Get<float>();
    me->AddControllerPitchInput(value);
}

void UPlayerMove::Move(const FInputActionValue& inputValue)
{
    FVector2D value = inputValue.Get<FVector2D>();

    // ���� �Է� ó��
    Direction.X = value.X;
    // �¿� �Է� ó��
    Direction.Y = value.Y;

    UE_LOG(LogTemp, Warning, TEXT("%f %f"), value.X, value.Y);
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
    // ����, ���� �޸��� �����
    if (Movement->MaxWalkSpeed > walkSpeed)
    {
        // �ȱ� �ӵ��� ��ȯ
        Movement->MaxWalkSpeed = walkSpeed;
    }
    else
    {
        Movement->MaxWalkSpeed = runSpeed;
    }
}
