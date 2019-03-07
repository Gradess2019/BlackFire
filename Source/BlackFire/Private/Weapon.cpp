// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

void UWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE! Damage %d, current ammo %d, max ammo %d, max ammo in magazine %d, reloading time %d, fire rate %d"), damage, currentAmmo, maxAmmo, maxAmmoInMagazine, reloadingTime, fireRate);
}

void UWeapon::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
}

void UWeapon::SetOwnerTeam(ETeam newTeam)
{
	currentTeam = newTeam;
}