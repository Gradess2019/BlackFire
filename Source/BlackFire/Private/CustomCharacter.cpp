// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCharacter.h"
#include "WeaponPoint.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealNetwork.h"

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicateMovement = true;
	this->bReplicates = true;
}

void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitWeaponPoint();
	InitWeaponSet();
	SetupAndAttachPrimaryWeapon();
}

void ACustomCharacter::InitWeaponPoint()
{
	TSet<class UActorComponent*> components = GetComponents();
	for (UActorComponent* component : components)
	{
		if (component->IsA(UWeaponPoint::StaticClass()))
		{
			weaponPoint = Cast<USceneComponent>(component);
		}
	}
}

void ACustomCharacter::InitWeaponSet()
{
	for (TSubclassOf<AWeaponActor> weaponClass : weaponClassSet)
	{
		FActorSpawnParameters weaponSpawnParameters;
		weaponSpawnParameters.Owner = this;
		weaponSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeaponActor* newWeapon = GetWorld()->SpawnActor<AWeaponActor>(weaponClass, GetActorTransform(), weaponSpawnParameters);
		newWeapon->SetWeaponOwner(this);
		newWeapon->SetActorHiddenInGame(true);
		weaponSet.Add(newWeapon);
	}
}

void ACustomCharacter::SetupAndAttachPrimaryWeapon()
{
	SetupPrimaryWeapon();
	AttachPrimaryWeapon();
}

void ACustomCharacter::SetupPrimaryWeapon()
{
	if (weaponSet.Num() > 0)
	{
		weapon = (weaponSet.Array())[0];
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("weaponSet is empty. Create default weapon.\n File: %s \n Function: %s \n Line: %d"), *FString(__FILE__), *FString(__FUNCTION__), __LINE__);
		weapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass(), GetActorTransform());
		weaponSet.Add(weapon);
	}
}

void ACustomCharacter::AttachPrimaryWeapon()
{
	if (weaponPoint)
	{
		weapon->SetActorHiddenInGame(false);
		AttachWeaponActor();
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("weaponPoint component is NULL.\n File: %s \n Function: %s \n Line: %d"), *FString(__FILE__), *FString(__FUNCTION__), __LINE__);
	}
}

void ACustomCharacter::AttachWeaponActor()
{
	weapon->AttachToComponent(weaponPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ACustomCharacter::TakeDamage(float damage)
{
	DecreaseHealth(damage);
	if (health <= 0.f)
	{
		Respawn_Implementation();
	}
}

void ACustomCharacter::DecreaseHealth(float decrement)
{
	health -= decrement;
}

void ACustomCharacter::Respawn_Implementation()
{
	if (!spawnPoint)
	{
		TArray<AActor*> spawnPoints;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), GetSpawnPointTag(), spawnPoints);
		if (spawnPoints.Num() > 0)
		{
			spawnPoint = spawnPoints[0];
		}
	}
	SetPositionToSpawn();

	health = 100.f;
}

void ACustomCharacter::SetPositionToSpawn()
{
	if (spawnPoint)
	{
		SetActorLocationAndRotation(spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation());
	}
}

void ACustomCharacter::SetTeam_Implementation(ETeam newTeam)
{
	if (team != newTeam)
	{
		team = newTeam;
		Respawn_Implementation();
	}
}

TSet<AWeaponActor*>* ACustomCharacter::GetWeaponSet()
{
	return &weaponSet;
}

AWeaponActor* ACustomCharacter::GetCurrentWeapon()
{
	return weapon;
}

FVector ACustomCharacter::GetEyesPosition()
{
	return FVector::ZeroVector;
}

FVector ACustomCharacter::GetEyesForwardVector()
{
	return FVector::ZeroVector;
}

uint32 ACustomCharacter::GetID()
{
	return GetUniqueID();
}

void ACustomCharacter::FireEvent()
{
	UE_LOG(LogTemp, Log, TEXT("FireEvent"));
}

void ACustomCharacter::ReloadEvent()
{
	UE_LOG(LogTemp, Log, TEXT("ReloadEvent"));
}

FName ACustomCharacter::GetSpawnPointTag()
{
	FName tag = FName("Start");

	// Не работает, почему?
	//switch (team)
	//{
	//case ETeam::Blue:
	//{
	//	tag = FName("Blue");
	//	break;

	//}

	//case ETeam::Red:
	//{
	//	tag = FName("Red");
	//	break;
	//}

	//default:
	//{
	//	tag = FName("Start");
	//	break;
	//}
	//}
	return tag;
}

void ACustomCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACustomCharacter, health);
}