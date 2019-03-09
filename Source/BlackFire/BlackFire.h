// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlackFire.generated.h"

UENUM()
enum class ETeam : uint8
{
	None,
	Blue,
	Red
};

UENUM()
enum class EShootingMode : uint8
{
	Single,
	SemiAuto,
	Auto
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	uint16 currentAmmoInMagazine;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	uint16 maxAmmoInMagazine;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	uint16 currentAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	uint16 maxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	float damage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	float reloadingTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	float fireRate;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon config")
	EShootingMode mode;

	FWeaponData()
	{
		currentAmmoInMagazine = 0;
		maxAmmoInMagazine = 0;
		currentAmmo = 0;
		maxAmmo = 0;
		damage = 0.f;
		reloadingTime = 0.f;
		fireRate = 0.f;
		mode = EShootingMode::Single;
	}
};