// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponOwner.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponOwner : public UInterface
{
	GENERATED_BODY()
};

class BLACKFIRE_API IWeaponOwner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetEyesPosition() = 0;
	virtual FVector GetEyesForwardVector() = 0;
	virtual uint32 GetID() = 0;
	virtual void FireEvent() = 0;
	virtual void ReloadEvent() = 0;
};
