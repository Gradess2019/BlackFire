// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerObserver.h"
#include "WeaponActor.h"
#include "BlackFire.h"
#include "UObject/Interface.h"
#include "PlayerSubject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerSubject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACKFIRE_API IPlayerSubject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void AttachObserver(IPlayerObserver* newObserver);
	virtual void DetachObserver(IPlayerObserver* observer);
	virtual void Notify();

	virtual FWeaponData GetWeaponData() = 0;

protected:

	TSet<IPlayerObserver*> observers;
};
