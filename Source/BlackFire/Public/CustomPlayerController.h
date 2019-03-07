// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActions.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLACKFIRE_API ACustomPlayerController : public APlayerController, public IGameActions
{
	GENERATED_BODY()
	
private:
	UCameraComponent* playerCamera;

	UFUNCTION()
	void BeginPlay() override;
	
	inline void InitControlledPawn();
	void InitCamera();

	void StartAttack() override;
	void StopAttack() override;
	void Reload() override;
	void SetupInputComponent() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void TurnAround(float value);
	
	bool IsInputZero(float value);
	bool IsCorrectCameraPitch(float value);

	inline void Move(FVector direction, float value);

	inline FVector GetRightDirection();
	inline FVector GetForwardDirection();

};
