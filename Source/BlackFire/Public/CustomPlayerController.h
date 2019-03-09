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
UCLASS(Blueprintable)
class BLACKFIRE_API ACustomPlayerController : public APlayerController, public IGameActions
{
	GENERATED_BODY()
public:
	ACustomPlayerController();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	TSubclassOf<UGUI> GUIClass;

	UCameraComponent* playerCamera;

	UFUNCTION()
	void BeginPlay() override;
	
	inline void InitControlledPawn();
	void InitCamera();

	
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

	inline void StartAttack() override;
	inline void StopAttack() override;
	inline void Reload() override;

};
