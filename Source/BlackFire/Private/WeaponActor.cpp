// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	InitFireTimeline();
	InitReloadTimeline();
	if (IsValidTimelines())
	{
		UE_LOG(LogTemp, Warning, TEXT("FUCKFUCKFUCK"));
	}
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

	FOnTimelineEventStatic fillMagazineEvent;
	fillMagazineEvent.BindUFunction(this, FName("FillMagazine"));
	reloadTimeline->SetTimelineFinishedFunc(fillMagazineEvent);

	reloadTimeline->RegisterComponent();
}

void AWeaponActor::StartFire()
{
	if (CanStartFireTimeline())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon info: Damage %f, current ammo %d, max ammo %d, max ammo in magazine %d, reloading time %f, fire rate %f"), damage, currentAmmo, maxAmmo, maxAmmoInMagazine, reloadingTime, fireRate);

		EnableShootingMode();
		fireTimeline->PlayFromStart();
	}
}

bool AWeaponActor::CanStartFireTimeline()
{
	return IsValidTimelines() && IsTimelinesStopped() && HasAmmoInMagazine();
}

bool AWeaponActor::IsValidTimelines()
{
	return IsValid(fireTimeline) && IsValid(reloadTimeline);
}

bool AWeaponActor::IsTimelinesStopped()
{
	return !fireTimeline->IsPlaying() && !reloadTimeline->IsPlaying();
}

bool AWeaponActor::HasAmmoInMagazine()
{
	return currentAmmoInMagazine > 0;
}

void AWeaponActor::EnableShootingMode()
{
	switch (mode)
	{
	
		case EShootingMode::Single:
		{
			fireTimeline->SetLooping(false);
			break;
		}

		case EShootingMode::Auto:
		{
			fireTimeline->SetLooping(true);
			break;
		}

	}
}

void AWeaponActor::StopFire()
{
	if (fireTimeline->IsPlaying())
	{
		fireTimeline->Stop();
	}
}

void AWeaponActor::Fire()
{
	currentAmmoInMagazine--;
	UE_LOG(LogTemp, Warning, TEXT("Firing! Current ammo in magazine: %d"), currentAmmoInMagazine);
	if (!HasAmmoInMagazine())
	{
		fireTimeline->Stop();
	}
}

void AWeaponActor::Reload()
{
	if (CanStartReloadTimeline())
	{
		UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
		reloadTimeline->PlayFromStart();
	}
}

bool AWeaponActor::CanStartReloadTimeline()
{
	return IsValidTimelines() && IsTimelinesStopped() && HasSpaceInMagazine() && HasAmmo();
}

bool AWeaponActor::HasSpaceInMagazine()
{
	return currentAmmoInMagazine < maxAmmoInMagazine;
}

bool AWeaponActor::HasAmmo()
{
	return currentAmmo > 0;
}

void AWeaponActor::SetOwnerTeam(ETeam newTeam)
{
	currentTeam = newTeam;
}

void AWeaponActor::FillMagazine()
{
	uint16 freeSpace = maxAmmoInMagazine - currentAmmoInMagazine;
	if (freeSpace > 0)
	{
		if (currentAmmo > freeSpace)
		{
			currentAmmo -= freeSpace;
		} else
		{
			freeSpace = currentAmmo;
			currentAmmo = 0;
		}
		currentAmmoInMagazine += freeSpace;
	}
	
}