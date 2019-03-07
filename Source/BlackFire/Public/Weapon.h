// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "BlackFire.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class BLACKFIRE_API UWeapon : public UObject
{
	GENERATED_BODY()

public:

	void Fire();
	void Reload();

	void SetOwnerTeam(ETeam newTeam);

private:

	uint8 currentAmmo;
	uint8 maxAmmoInMagazine;
	uint16 maxAmmo;

	float damage;
	float reloadingTime;
	float fireRate;

	bool isFiring;
	bool isReloading;

	ETeam currentTeam;
};
