// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameActions.h"
#include "CustomCharacter.h"
#include "AIController.h"
#include "CustomNPCController.generated.h"

/**
 * NPC controller class
 */
UCLASS()
class BLACKFIRE_API ACustomNPCController : public AAIController, public IGameActions
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void BeginPlay() override;

	void Client_StartAttack() override;
	void Client_StopAttack() override;
	void Client_Reload() override;

};
