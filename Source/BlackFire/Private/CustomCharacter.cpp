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

