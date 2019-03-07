// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE! Damage %d, current ammo %d, max ammo %d, max ammo in magazine %d, reloading time %d, fire rate %d"), damage, currentAmmo, maxAmmo, maxAmmoInMagazine, reloadingTime, fireRate);
}

void AWeaponActor::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
}

void AWeaponActor::SetOwnerTeam(ETeam newTeam)
{
	currentTeam = newTeam;
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineEventStatic fireFunc;
	fireFunc.BindUFunction(this, FName("Reload"));
	timeline.SetTimelineLength(1.f);
	timeline.AddEvent(0.f, fireFunc);
}

void AWeaponActor::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
