// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestroyableObject.h"
#include "BlackFire.h"
#include "WeaponActor.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

UCLASS(Abstract)
class BLACKFIRE_API ACustomCharacter : public ACharacter, public IDestroyableObject
{
	GENERATED_BODY()

public:

	ACustomCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TakeDamage(float damage) override;

	void Die();

	TSet<AWeaponActor*>* GetWeaponSet();
	
	AWeaponActor* GetCurrentWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	TSet<TSubclassOf<AWeaponActor> > weaponClassSet;

	float health;

	AWeaponActor* weapon;
	TSet<AWeaponActor*> weaponSet;

	ETeam team;

	virtual void BeginPlay() override;
};
