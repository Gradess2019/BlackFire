// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#define DestroyableObjectTrace ECC_GameTraceChannel1

AWeaponActor::AWeaponActor() : fireTraceTag(FName("FireTraceTag"))
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	InitFireTimeline();
	InitReloadTimeline();
	InitLineTrace();
}

void AWeaponActor::InitFireTimeline()
{
	fireTimeline = NewObject<UTimelineComponent>(this, "FireTimeline");
	const float fireTimelineLength = 60.f / data.fireRate;
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
	reloadTimeline->SetTimelineLength(data.reloadingTime);
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

void AWeaponActor::InitLineTrace()
{
	GetWorld()->DebugDrawTraceTag = fireTraceTag;
}

void AWeaponActor::StartFire()
{
	if (CanStartFireTimeline())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon info: Damage %f, current ammo %d, max ammo %d, max ammo in magazine %d, reloading time %f, fire rate %f"), data.damage, data.currentAmmo, data.maxAmmo, data.maxAmmoInMagazine, data.reloadingTime, data.fireRate);

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
	return data.currentAmmoInMagazine > 0;
}

void AWeaponActor::EnableShootingMode()
{
	switch (data.mode)
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
	FHitResult hit = GetHit();
	IDestroyableObject* hitObject = Cast<IDestroyableObject>(hit.GetActor());

	if (hitObject)
	{
		hitObject->TakeDamage(data.damage);
	}

	data.currentAmmoInMagazine--;
	UE_LOG(LogTemp, Warning, TEXT("Current ammo in magazine: %d"), data.currentAmmoInMagazine);
	CheckAmmoInMagazine();
}

FHitResult AWeaponActor::GetHit()
{
	FHitResult hit = FHitResult(EForceInit::ForceInit);

	FVector start = owner->GetEyesPosition();
	FVector end = owner->GetEyesForwardVector() * 100000.f;

	FCollisionObjectQueryParams collisionObjectParams(DestroyableObjectTrace);
	FCollisionQueryParams collisionParams;
	collisionParams.bTraceComplex = true;
	collisionParams.TraceTag = fireTraceTag;
	collisionParams.AddIgnoredActor(owner->GetID());
	bool isHitted = GetWorld()->LineTraceSingleByObjectType(
		hit,
		start,
		end + owner->GetEyesPosition(),
		collisionObjectParams,
		collisionParams
	);

	return hit;
}

void AWeaponActor::Reload()
{
	if (CanStartReloadTimeline())
	{
		reloadTimeline->PlayFromStart();
	}
}

bool AWeaponActor::CanStartReloadTimeline()
{
	return IsValidTimelines() && IsTimelinesStopped() && HasSpaceInMagazine() && HasAmmo();
}

bool AWeaponActor::HasSpaceInMagazine()
{
	return data.currentAmmoInMagazine < data.maxAmmoInMagazine;
}

bool AWeaponActor::HasAmmo()
{
	return data.currentAmmo > 0;
}

void AWeaponActor::CheckAmmoInMagazine()
{
	if (!HasAmmoInMagazine())
	{
		fireTimeline->Stop();
		if (CanStartReloadTimeline())
		{
			reloadTimeline->PlayFromStart();
		}
	}
}

void AWeaponActor::SetOwnerTeam(ETeam newTeam)
{
	currentTeam = newTeam;
}

void AWeaponActor::SetWeaponOwner(IWeaponOwner* newOwner)
{
	owner = newOwner;
}

void AWeaponActor::FillMagazine()
{
	uint16 freeSpace = data.maxAmmoInMagazine - data.currentAmmoInMagazine;
	if (freeSpace > 0)
	{
		if (data.currentAmmo > freeSpace)
		{
			data.currentAmmo -= freeSpace;
		} else
		{
			freeSpace = data.currentAmmo;
			data.currentAmmo = 0;
		}
		data.currentAmmoInMagazine += freeSpace;
	}
	
}