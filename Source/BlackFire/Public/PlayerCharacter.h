// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacter.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

class ACustomPlayerController;
/**
 * 
 */
UCLASS()
class BLACKFIRE_API APlayerCharacter : public ACustomCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

private:
	UCameraComponent* cameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	float zOffset;

	inline void SetController();

	inline void InitCamera();
	inline void CreateAndAttachCamera();
	inline void CreateCamera();
	inline void AttachCamera();
	inline void SetCameraRelativeLocation();

	inline void SetUseControllerRotation();
};
