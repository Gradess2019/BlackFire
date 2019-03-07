// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
	InitFireTimeline();
	InitReloadTimeline();
}

void AWeaponActor::InitFireTimeline()
{
	fireTimeline = NewObject<UTimelineComponent>(this, "FireTimeline");
	const float fireTimelineLength = 60.f / fireRate;
	fireTimeline->SetTimelineLength(fireTimelineLength);
	fireTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	fireTimeline->SetNetAddressable();
	
	FOnTimelineEvent fireEvent;
	fireEvent.BindUFunction(this, FName("Fire"));
	fireTimeline->AddEvent(0.f, fireEvent);

	fireTimeline->RegisterComponent();
}

void AWeaponActor::InitReloadTimeline()
{
	reloadTimeline = NewObject<UTimelineComponent>(this, "ReloadTimeline");
	reloadTimeline->SetTimelineLength(reloadingTime);
	reloadTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
	reloadTimeline->SetNetAddressable();

	FOnTimelineEvent reloadEvent;
	reloadEvent.BindUFunction(this, FName("Reload"));
	reloadTimeline->AddEvent(0.f, reloadEvent);

	reloadTimeline->RegisterComponent();
}

void AWeaponActor::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon info: Damage %f, current ammo %d, max ammo %d, max ammo in magazine %d, reloading time %f, fire rate %f"), damage, currentAmmo, maxAmmo, maxAmmoInMagazine, reloadingTime, fireRate);
}

void AWeaponActor::StopFire()
{
	
}

void AWeaponActor::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing!"));
}

void AWeaponActor::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
}

void AWeaponActor::SetOwnerTeam(ETeam newTeam)
{
	currentTeam = newTeam;
}