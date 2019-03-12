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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void TakeDamage(float damage) override;

	UFUNCTION()
	void DecreaseHealth(float decrement);

	//UFUNCTION(NetMulticast, Unreliable)
	//	Multicast_TakeDamge();

	UFUNCTION(BlueprintCallable)
	void Respawn();

	TSet<AWeaponActor*>* GetWeaponSet();
	
	AWeaponActor* GetCurrentWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	TSet<TSubclassOf<AWeaponActor> > weaponClassSet;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Character configuration")
	float health;

	AWeaponActor* weapon;
	TSet<AWeaponActor*> weaponSet;

	ETeam team;

	class USceneComponent* weaponPoint;

	virtual void BeginPlay() override;
	virtual FVector GetEyesPosition() override;
	virtual FVector GetEyesForwardVector() override;
	virtual uint32 GetID() override;
	virtual void FireEvent() override;
	virtual void ReloadEvent() override;
	
	void AttachWeaponActor();
};
