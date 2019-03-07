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
	
	void EnableShootingMode();

	UFUNCTION()
	void FillMagazine();
	
};
