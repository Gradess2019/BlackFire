// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "WeaponOwner.h"
#include "DestroyableObject.h"
#include "BlackFire.h"
#include "Sound/SoundWave.h"
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

	void StopReload();

	void SetOwnerTeam(ETeam newTeam);
	void SetWeaponOwner(IWeaponOwner* newOwner);

	FWeaponData GetData();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon configuration")
	FWeaponData data;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon configuration")
	USoundWave* shotSound; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon configuration")
	USoundWave* reloadingStartSound;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon configuration")
	USoundWave* reloadingFinishSound;

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

	void EnableShootingMode();

	inline bool CanStartFireTimeline();
	inline bool CanStartReloadTimeline();
	inline bool IsValidTimelines();
	inline bool IsTimelinesStopped();
	inline bool HasAmmoInMagazine();

	inline bool HasSpaceInMagazine();
	inline bool HasAmmo();

	void CheckAmmoInMagazine();

	void StartReload();

	UFUNCTION()
	void FillMagazine();
	
	FHitResult GetHit();

	void PlaySound(USoundWave* sound);
	void PlayShotSound();
	void PlayReloadingStartSound();
	void PlayReloadingFinishSound();

	void Client_AddDamage(IDestroyableObject* damagedObject);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_AddDamage(UObject* object, const float damage);

	void AddDamage(UObject* object, const float damage);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_FireEvent(UObject* context);

	

};
