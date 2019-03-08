// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "CustomPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	SetController();
	SetUseControllerRotation();
	CreateAndAttachCamera();
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

void APlayerCharacter::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	SetCameraRelativeLocation();
}

void APlayerCharacter::SetCameraRelativeLocation()
{
	FVector relativeLocation = FVector(0.f, 0.f, 60.f);
	cameraComponent->SetRelativeLocation(relativeLocation);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (weaponSet.Num() > 0)
	{
		weapon = (weaponSet.Array())[0];
	} else
	{
		weapon = GetWorld()->SpawnActor<APistol>(APistol::StaticClass(), GetActorTransform());
	}
}