// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "CustomPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	//Default zOffset value
	zOffset = 0.f;

	SetController();
	InitCamera();
	SetUseControllerRotation();	
}

void APlayerCharacter::SetController()
{
	AIControllerClass = ACustomPlayerController::StaticClass();
}

void APlayerCharacter::InitCamera()
{
	CreateAndAttachCamera();
	SetCameraRelativeLocation();
}

void APlayerCharacter::CreateAndAttachCamera()
{
	CreateCamera();
	AttachCamera();
}

void APlayerCharacter::CreateCamera()
{
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

void APlayerCharacter::AttachCamera()
{
	cameraComponent->SetupAttachment(RootComponent);
}

void APlayerCharacter::SetCameraRelativeLocation()
{
	FVector deltaRelativeLocation = FVector(0.f, 0.f, zOffset);
	cameraComponent->AddRelativeLocation(deltaRelativeLocation);
}

void APlayerCharacter::SetUseControllerRotation()
{
	this->bUseControllerRotationPitch = true;
	this->bUseControllerRotationYaw = true;
	this->bUseControllerRotationRoll = true;
}
