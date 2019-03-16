// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestroyableObject.h"
#include "BlackFire.h"
#include "WeaponActor.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

UCLASS(Abstract)
class BLACKFIRE_API ACustomCharacter : public ACharacter, public IDestroyableObject, public IWeaponOwner
{
	GENERATED_BODY()

public:

	ACustomCharacter();

	UFUNCTION()
	void TakeDamage(float damage) override;

	//UFUNCTION(NetMulticast, Unreliable)
	//	Multicast_TakeDamge();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Respawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTeam(ETeam newTeam);

	TSet<AWeaponActor*>* GetWeaponSet();
	
	AWeaponActor* GetCurrentWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	TSet<TSubclassOf<AWeaponActor> > weaponClassSet;
	AWeaponActor* weapon;
	TSet<AWeaponActor*> weaponSet;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Character configuration")
	float health;

	UPROPERTY(BlueprintReadOnly)
	ETeam team;

	UPROPERTY(BlueprintReadWrite)
	AActor* spawnPoint;

	class USceneComponent* weaponPoint;

	virtual void BeginPlay() override;
	void InitWeaponPoint();
	void InitWeaponSet();
	void SetupAndAttachPrimaryWeapon();
	void SetupPrimaryWeapon();
	void AttachPrimaryWeapon();
	void AttachWeaponActor();

	UFUNCTION(BlueprintCallable)
	void SetPositionToSpawn();
	
	void DecreaseHealth(float decrement);

	virtual FVector GetEyesPosition() override;
	virtual FVector GetEyesForwardVector() override;
	virtual uint32 GetID() override;
	virtual void FireEvent() override;
	virtual void ReloadEvent() override;

	FName GetSpawnPointTag();

	
};
