// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomCharacter.h"

ACustomCharacter::ACustomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ACustomCharacter::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0.f)
	{
		Die();
	}
	UE_LOG(LogTemp, Warning, TEXT("Taked damage %d. Current health %d"), damage, health);
}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACustomCharacter::Die()
{
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

	for (TSubclassOf<AWeaponActor> weaponClass : weaponClassSet)
	{
		FActorSpawnParameters weaponSpawnParameters;
		weaponSpawnParameters.Owner = this;
		weaponSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeaponActor* newWeapon = GetWorld()->SpawnActor<AWeaponActor>(weaponClass, GetActorTransform(), weaponSpawnParameters);
		weaponSet.Add(newWeapon);
	}

	if (weaponSet.Num() > 0)
	{
		weapon = (weaponSet.Array())[0];
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("weaponSet is empty. Create default weapon.\n File: %s \n Function: %s \n Line: %d"), *FString(__FILE__), *FString(__FUNCTION__), __LINE__);
		weapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass(), GetActorTransform());
	}