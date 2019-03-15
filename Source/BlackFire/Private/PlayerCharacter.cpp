// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "CustomPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	SetController();
	SetUseControllerRotation();
	CreateAndAttachCamera();

	bReplicates = true;
	bReplicateMovement = true;
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

void APlayerCharacter::TakeDamage(float damage)
{
	Super::TakeDamage(damage);
	Notify();
	//if (Role < ROLE_Authority)
	//{
	//	Server_Notify();
	//} else
	//{
	//	Notify();
	//}
}

void APlayerCharacter::Client_Notify_Implementation()
{
	Notify();
}

void APlayerCharacter::Server_Notify_Implementation(UObject* context)
{
	//Notify(UObject* context);
}

bool APlayerCharacter::Server_Notify_Validate(UObject* context)
{
	IPlayerSubject* subject = Cast<IPlayerSubject>(context);
	return subject != nullptr;
}

void APlayerCharacter::CreateAndAttachCamera()
{
	CreateCamera();
	AttachCamera();
}

void APlayerCharacter::CreateCamera()
{
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetIsReplicated(true);
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

FVector APlayerCharacter::GetEyesPosition()
{
	return cameraComponent->GetComponentLocation();
}

FVector APlayerCharacter::GetEyesForwardVector()
{
	return cameraComponent->GetForwardVector();
}

void APlayerCharacter::FireEvent()
{
	Notify();
	//if (Role < ROLE_Authority)
	//{
	//	Server_Notify();
	//} else
	//{
	//	Notify();
	//}
	//Client_Notify();
}

void APlayerCharacter::ReloadEvent()
{
	Notify();
}

FWeaponData APlayerCharacter::GetWeaponData()
{
	return weapon->GetData();
}

void APlayerCharacter::NextWeapon()
{

	TArray<AWeaponActor*> weaponArray = weaponSet.Array();
	int32 currentWeaponID = 0;

	if (weaponArray.Num() > 1 && weaponArray.Find(weapon, currentWeaponID))
	{
		int32 newWeaponID = currentWeaponID + 1;

		if (!weaponArray.IsValidIndex(newWeaponID))
		{
			newWeaponID = 0;
		}
		SetWeapon(newWeaponID);
		AttachWeaponActor();
	}
	Notify();
}

void APlayerCharacter::SetWeapon(int32 id)
{
	weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	weapon->SetActorHiddenInGame(true);
	weapon->StopReload();

	weapon = GetWeaponById(id);
	weapon->SetActorHiddenInGame(false);
}

AWeaponActor* APlayerCharacter::GetWeaponById(int32 id)
{
	TArray<AWeaponActor*> weaponArray = weaponSet.Array();

	if (weaponArray.IsValidIndex(id))
	{
		return weaponArray[id];
	}

	return nullptr;
}

void APlayerCharacter::PreviousWeapon()
{
	TArray<AWeaponActor*> weaponArray = weaponSet.Array();
	int32 currentWeaponID = 0;

	if (weaponArray.Num() > 1 && weaponArray.Find(weapon, currentWeaponID))
	{
		int32 newWeaponID = currentWeaponID - 1;
		if (!weaponArray.IsValidIndex(newWeaponID))
		{
			newWeaponID = weaponArray.Num() - 1;
		}
		SetWeapon(newWeaponID);
		AttachWeaponActor();
	}

	Notify();
}