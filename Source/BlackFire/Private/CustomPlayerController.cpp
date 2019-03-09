// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "GUI.h"

ACustomPlayerController::ACustomPlayerController()
{
	this->bAttachToPawn = true;
}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitControlledPawn();
	InitCamera();

	APlayerCharacter* player = Cast<APlayerCharacter>(controlledPawn);

	UGUI* gui = CreateWidget<UGUI>(this, GUIClass);
	if (gui)
	{
		gui->AddToViewport();
		player->AttachObserver((IPlayerObserver*)gui);
	}
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

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::LookUp);
	InputComponent->BindAxis("TurnAround", this, &ACustomPlayerController::TurnAround);

	InputComponent->BindAction("PreviousWeapon", EInputEvent::IE_Pressed, this, &ACustomPlayerController::PreviousWeapon);
	InputComponent->BindAction("NextWeapon", EInputEvent::IE_Released, this, &ACustomPlayerController::NextWeapon);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACustomPlayerController::Jump);
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

void ACustomPlayerController::NextWeapon()
{
	GetControlledPlayer()->NextWeapon();
}

APlayerCharacter* ACustomPlayerController::GetControlledPlayer()
{
	return Cast<APlayerCharacter>(controlledPawn);
}

void ACustomPlayerController::PreviousWeapon()
{
	GetControlledPlayer()->PreviousWeapon();
}

void ACustomPlayerController::Jump()
{
	GetControlledPlayer()->Jump();
}

void ACustomPlayerController::StartAttack()
{
	controlledPawn->GetCurrentWeapon()->StartFire();
}

void ACustomPlayerController::StopAttack()
{
	controlledPawn->GetCurrentWeapon()->StopFire();
}

void ACustomPlayerController::Reload()
{
	controlledPawn->GetCurrentWeapon()->Reload();
}