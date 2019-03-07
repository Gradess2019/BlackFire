// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestroyableObject.h"
#include "BlackFire.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

UCLASS()
class BLACKFIRE_API ACustomCharacter : public ACharacter, public IDestroyableObject
{
	GENERATED_BODY()

public:

	ACustomCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TakeDamage(float damage) override;

	void Die();

	TSet<UWeapon*>* GetWeaponSet();
	
	UWeapon* GetCurrentWeapon();

protected:

	float health;

	UWeapon* weapon;
	TSet<UWeapon*> weaponSet;

	ETeam team;

};
