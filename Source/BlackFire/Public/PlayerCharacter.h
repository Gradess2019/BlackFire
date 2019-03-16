// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacter.h"
#include "Pistol.h"
#include "GUI.h"
#include "WeaponOwner.h"
#include "PlayerSubject.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

class ACustomPlayerController;

UCLASS()
class BLACKFIRE_API APlayerCharacter : public ACustomCharacter, public IPlayerSubject
{
	GENERATED_BODY()
	
public:

	APlayerCharacter();

	void TakeDamage(float damage) override;
	void NextWeapon();
	void PreviousWeapon();

	virtual FWeaponData GetWeaponData() override;

private:

	UCameraComponent* cameraComponent;

	inline void SetController();
	inline void SetUseControllerRotation();

	inline void CreateAndAttachCamera();
	inline void CreateCamera();
	inline void AttachCamera();

	void SetWeapon(int32 id);
	AWeaponActor* GetWeaponById(int32 id);

	void OnConstruction(const FTransform&) override;
	inline void SetCameraRelativeLocation();

	FVector GetEyesPosition() override;
	FVector GetEyesForwardVector() override;
	void FireEvent() override;
	void ReloadEvent() override;
	
	UFUNCTION(Reliable, Client)
	void Client_Notify();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Notify(UObject* context);
};
