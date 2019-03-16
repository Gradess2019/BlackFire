// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "GUI.h"
#include "Kismet/KismetSystemLibrary.h"

inline FColor GetDebugColorMessage(bool isSuccess);

#define SUCCESS true
#define FAILURE false

ACustomPlayerController::ACustomPlayerController()
{
	this->bAttachToPawn = true;
}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitControlledPawn();
	InitCamera();
	InitGUI();
}

void ACustomPlayerController::InitControlledPawn()
{
	controlledPawn = Cast<ACustomCharacter>(GetPawn());

	if (controlledPawn)
	{
		PrintDebugReplicationMessage(FString("Controlled pawn is true"), SUCCESS);
	}
}

void ACustomPlayerController::PrintDebugReplicationMessage(FString message, bool isSuccess)
{
	FColor color = GetDebugColorMessage(isSuccess);
	FString resultMessage = GetGamePrefix() + message;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, color, resultMessage);
}

FColor GetDebugColorMessage(bool isSuccess)
{
	return (isSuccess) ? FColor::Green : FColor::Yellow;
}

FString ACustomPlayerController::GetGamePrefix()
{
	return (HasAuthority()) ? FString("Server: ") : FString("Client: ");
}

void ACustomPlayerController::InitCamera()
{
	if (controlledPawn)
	{
		TSet<UActorComponent*> components = controlledPawn->GetComponents();
		for (UActorComponent* component : components)
		{
			if (component->IsA(UCameraComponent::StaticClass()))
			{
				playerCamera = Cast<UCameraComponent>(component);
				PrintDebugReplicationMessage(FString("Camera was successfully initialized"), SUCCESS);
				break;
			}
		}
	}
}

void ACustomPlayerController::InitGUI()
{
	if (controlledPawn)
	{
		APlayerCharacter* player = GetControlledPlayer();

		UGUI* gui = CreateWidget<UGUI>(this, GUIClass);
		if (gui)
		{
			gui->AddToViewport();
			player->AttachObserver((IPlayerObserver*)gui);
		}
	}
}

APlayerCharacter* ACustomPlayerController::GetControlledPlayer()
{
	return Cast<APlayerCharacter>(controlledPawn);
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
	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &ACustomPlayerController::Client_StartAttack);
	InputComponent->BindAction("Attack", EInputEvent::IE_Released, this, &ACustomPlayerController::Client_StopAttack);
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACustomPlayerController::Client_Reload);
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

void ACustomPlayerController::PreviousWeapon()
{
	GetControlledPlayer()->PreviousWeapon();
}

void ACustomPlayerController::NextWeapon()
{
	GetControlledPlayer()->NextWeapon();
}

void ACustomPlayerController::Jump()
{
	GetControlledPlayer()->Jump();
}

void ACustomPlayerController::Client_StartAttack()
{
	if (Role < ROLE_Authority)
	{
		Server_StartAttack(controlledPawn);
	} else
	{
		StartAttack(controlledPawn);
	}
}

void ACustomPlayerController::Server_StartAttack_Implementation(ACustomCharacter* controlledPawn)
{
	StartAttack(controlledPawn);
}

bool ACustomPlayerController::Server_StartAttack_Validate(ACustomCharacter* controlledPawn)
{
	return IsValid(controlledPawn);
}

void ACustomPlayerController::StartAttack(ACustomCharacter* controlledPawn)
{
	controlledPawn->GetCurrentWeapon()->StartFire();
}

void ACustomPlayerController::Client_StopAttack()
{
	if (Role < ROLE_Authority)
	{
		Server_StopAttack(controlledPawn);
	} else
	{
		StopAttack(controlledPawn);
	}
}

void ACustomPlayerController::Server_StopAttack_Implementation(ACustomCharacter* controlledPawn)
{
	StopAttack(controlledPawn);
}

bool ACustomPlayerController::Server_StopAttack_Validate(ACustomCharacter* controlledPawn)
{
	return IsValid(controlledPawn);
}

void ACustomPlayerController::StopAttack(ACustomCharacter* controlledPawn)
{
	controlledPawn->GetCurrentWeapon()->StopFire();
}

void ACustomPlayerController::Client_Reload()
{
	if (Role < ROLE_Authority)
	{
		Server_Reload(controlledPawn);
	} else
	{
		Reload(controlledPawn);
	}
}

void ACustomPlayerController::Server_Reload_Implementation(ACustomCharacter* controlledPawn)
{
	Reload(controlledPawn);
}

bool ACustomPlayerController::Server_Reload_Validate(ACustomCharacter* controlledPawn)
{
	return IsValid(controlledPawn);
}

void ACustomPlayerController::Reload(ACustomCharacter* controlledPawn)
{
	controlledPawn->GetCurrentWeapon()->Reload();
}

