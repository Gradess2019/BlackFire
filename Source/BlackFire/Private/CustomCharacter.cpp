// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCharacter.h"
#include "WeaponPoint.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "UnrealNetwork.h"

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicateMovement = true;
	this->bReplicates = true;
}

void ACustomCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACustomCharacter, health);
}

void ACustomCharacter::TakeDamage(float damage)
{
	if (Role < ROLE_Authority)
	{
		Server_TakeDamage(damage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Client takeDamage"));
	} else
	{
		DecreaseHealth(damage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Server takeDamage"));
	}
}

void ACustomCharacter::Server_TakeDamage_Implementation(float damage)
{
	DecreaseHealth(damage);
}

bool ACustomCharacter::Server_TakeDamage_Validate(float damage)
{
	return true;
}

void ACustomCharacter::DecreaseHealth(float decrement)
{
	health -= decrement;
}

void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACustomCharacter::Die()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		AActor* playerStart = actors[0];
		this->SetActorLocationAndRotation(playerStart->GetActorLocation(), playerStart->GetActorRotation());
	}
	UE_LOG(LogTemp, Warning, TEXT("Character is dead"));
}

TSet<AWeaponActor*>* ACustomCharacter::GetWeaponSet()
{
	return &weaponSet;
}

AWeaponActor* ACustomCharacter::GetCurrentWeapon()
{
	return weapon;
}

void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();

	TSet<class UActorComponent*> components = GetComponents();
	for (UActorComponent* component : components)
	{
		if (component->IsA(UWeaponPoint::StaticClass()))
		{
			weaponPoint = Cast<USceneComponent>(component);
		}
	}

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

	if (weaponSet.Num() > 0)
	{
		weapon = (weaponSet.Array())[0];
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("weaponSet is empty. Create default weapon.\n File: %s \n Function: %s \n Line: %d"), *FString(__FILE__), *FString(__FUNCTION__), __LINE__);
		weapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass(), GetActorTransform());
		weaponSet.Add(weapon);
	}

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