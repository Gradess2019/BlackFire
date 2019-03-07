// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "CustomPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	SetController();
	SetUseControllerRotation();
	InitCamera();
}

void APlayerCharacter::SetController()
{
	AIControllerClass = ACustomPlayerController::StaticClass();
}

void APlayerCharacter::SetUseControllerRotation()
{
	this->bUseControllerRotationPitch = true;
	this->bUseControllerRotationYaw = true;
	this->bUseControllerRotationRoll = true;
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



void APlayerCharacter::BeginPlay()
{
	SetCameraRelativeLocation();
}

void APlayerCharacter::SetCameraRelativeLocation()
{
	FVector relativeLocation = FVector(0.f, 0.f, zOffset);
	cameraComponent->SetRelativeLocation(relativeLocation);
}