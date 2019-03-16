// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestroyableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDestroyableObject : public UInterface
{
	GENERATED_BODY()
};

class BLACKFIRE_API IDestroyableObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void TakeDamage(float damage) = 0;
};
