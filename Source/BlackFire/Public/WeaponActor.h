// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponOwner.h"
#include "DestroyableObject.h"
#include "BlackFire.h"
#include "PlayerSubject.h"
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
	void SetWeaponOwner(IWeaponOwner* newOwner);

	FWeaponData GetData();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon configuration")
	FWeaponData data;
	
	ETeam currentTeam;

	const FName fireTraceTag;

	UTimelineComponent* fireTimeline;
	UTimelineComponent* reloadTimeline;

	IWeaponOwner* owner;

private:
	virtual void BeginPlay() override;

	void InitFireTimeline();
	void InitReloadTimeline();
	inline void InitLineTrace();

	inline bool IsValidTimelines();
	inline bool IsTimelinesStopped();
	inline bool CanStartFireTimeline();
	inline bool CanStartReloadTimeline();

	inline bool HasAmmoInMagazine();
	inline bool HasSpaceInMagazine();
	inline bool HasAmmo();

	void CheckAmmoInMagazine();
	
	void EnableShootingMode();

	FHitResult GetHit();
	
	UFUNCTION()
	void FillMagazine();
	
};
