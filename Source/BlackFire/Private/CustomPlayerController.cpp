// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"

void ACustomPlayerController::BeginPlay()
{
	InitControlledPawn();
	InitCamera();
}

void ACustomPlayerController::InitControlledPawn()
{
	controlledPawn = Cast<ACustomCharacter>(GetPawn());
}

void ACustomPlayerController::InitCamera()
{
	TSet<UActorComponent*> components = controlledPawn->GetComponents();
	for (UActorComponent* component : components)
	{
		if (component->IsA(UCameraComponent::StaticClass()))
		{
			playerCamera = Cast<UCameraComponent>(component);
			break;
		}
	}
}

void ACustomPlayerController::StartAttack()
{
	//controlledPawn->GetCurrentWeapon()->StartFire();
}

void ACustomPlayerController::StopAttack()
{
	//controlledPawn->GetCurrentWeapon()->StopFire();
}

void ACustomPlayerController::Reload()
{
	controlledPawn->GetCurrentWeapon()->Reload();
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::LookUp);
	InputComponent->BindAxis("TurnAround", this, &ACustomPlayerController::TurnAround);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACustomPlayerController::StartAttack);
	InputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACustomPlayerController::StopAttack);
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACustomPlayerController::Reload);
}

void ACustomPlayerController::MoveForward(float value)
{
	if (!IsInputZero(value))
	{
		FVector direction = GetForwardDirection();
		Move(direction, value);
	}
}

bool ACustomPlayerController::IsInputZero(float value)
{
	return value == 0.f;
}

FVector ACustomPlayerController::GetForwardDirection()
{
	FRotator yawRotation = FRotator(0.f, controlledPawn->GetActorRotation().Yaw, 0.f);
	return UKismetMathLibrary::GetForwardVector(yawRotation);
}

void ACustomPlayerController::Move(FVector direction, float value)
{
	controlledPawn->AddMovementInput(direction, value);
}

void ACustomPlayerController::MoveRight(float value)
{
	if (!IsInputZero(value))
	{
		FVector direction = GetRightDirection();
		Move(direction, value);
	}
}

FVector ACustomPlayerController::GetRightDirection()
{
	return UKismetMathLibrary::GetRightVector(controlledPawn->GetActorRotation());
}

void ACustomPlayerController::LookUp(float value)
{
	if (!IsInputZero(value) && IsCorrectCameraPitch(value))
	{
		FRotator newRotation = FRotator(playerCamera->RelativeRotation.Pitch + value, playerCamera->RelativeRotation.Yaw, 0.f);
		playerCamera->SetRelativeRotation(newRotation);
	}
}

bool ACustomPlayerController::IsCorrectCameraPitch(float value)
{
	const float newPitch = playerCamera->RelativeRotation.Pitch + value;
	const float bound = 87.f;
	return -bound < newPitch && newPitch < bound;
}

void ACustomPlayerController::TurnAround(float value)
{
	if (!IsInputZero(value))
	{
		AddYawInput(value);
	}
}

