// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "CustomCharacter.h"
#include "UObject/Interface.h"
#include "GameActions.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameActions : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKFIRE_API IGameActions
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	ACustomCharacter* controlledPawn;

	virtual void StartAttack() = 0;
	virtual void StopAttack() = 0;
	virtual void Reload() = 0;

	virtual void DropWeapon(AWeaponActor*);

};
