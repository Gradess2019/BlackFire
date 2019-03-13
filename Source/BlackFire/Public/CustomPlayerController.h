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

	UPROPERTY(EditDefaultsOnly, Category = "Character configuration")
	TSubclassOf<UGUI> GUIClass;

	UCameraComponent* playerCamera;

private:

	UFUNCTION()
	void BeginPlay() override;
	
	inline void InitControlledPawn();
	void InitCamera();
	void InitGUI();


	void PrintDebugReplicationMessage(FString message, bool isSuccess);
	inline FString GetGamePrefix();

	void SetupInputComponent() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void TurnAround(float value);
	
	bool IsInputZero(float value);
	bool IsCorrectCameraPitch(float value);

	inline void NextWeapon();
	inline void PreviousWeapon();
	inline void Jump();
	inline APlayerCharacter* GetControlledPlayer();

	inline void Move(FVector direction, float value);

	inline FVector GetRightDirection();
	inline FVector GetForwardDirection();

	// GameActions implementation
	inline void Client_StartAttack() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StartAttack(ACustomCharacter* controlledPawn);

	void StartAttack(ACustomCharacter* controlledPawn);

	inline void Client_StopAttack() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopAttack(ACustomCharacter* controlledPawn);

	void StopAttack(ACustomCharacter* controlledPawn);

	inline void Client_Reload() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Reload(ACustomCharacter* controlledPawn);

	void Reload(ACustomCharacter* controlledPawn);
};
