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

	uint16 currentAmmoInMagazine;
	uint16 maxAmmoInMagazine;
	uint16 currentAmmo;
	uint16 maxAmmo;

	float damage;
	float reloadingTime;
	float fireRate;

	ETeam currentTeam;

	UTimelineComponent* fireTimeline;
	UTimelineComponent* reloadTimeline;

private:
	virtual void BeginPlay() override;

	void InitFireTimeline();
	void InitReloadTimeline();

	inline bool IsValidTimelines();
	inline bool IsTimelinesStopped();
	inline bool CanStartFireTimeline();
	inline bool CanStartReloadTimeline();

	inline bool HasAmmoInMagazine();
	inline bool HasSpaceInMagazine();
	inline bool HasAmmo();
	
};
