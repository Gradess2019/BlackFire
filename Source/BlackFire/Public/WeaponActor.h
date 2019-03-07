// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "BlackFire.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class BLACKFIRE_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponActor();

	UFUNCTION()
	void StartFire();
	
	UFUNCTION()
	void StopFire();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Reload();

	void SetOwnerTeam(ETeam newTeam);

protected:

	uint8 currentAmmo;
	uint8 maxAmmoInMagazine;
	uint16 maxAmmo;

	float damage;
	float reloadingTime;
	float fireRate;

	bool isFiring;
	bool isReloading;

	ETeam currentTeam;

	UTimelineComponent* fireTimeline;
	UTimelineComponent* reloadTimeline;

private:

	void InitFireTimeline();
	void InitReloadTimeline();

};
