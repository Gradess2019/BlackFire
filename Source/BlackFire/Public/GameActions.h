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

class BLACKFIRE_API IGameActions
{
	GENERATED_BODY()

protected:

	ACustomCharacter* controlledPawn;

	virtual void Client_StartAttack() = 0;
	virtual void Client_StopAttack() = 0;
	virtual void Client_Reload() = 0;

	virtual void DropWeapon(AWeaponActor*);

};
