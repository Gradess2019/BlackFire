// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestroyableObject.h"
#include "GameFramework/Actor.h"
#include "PhysicalObject.generated.h"

UCLASS()
class BLACKFIRE_API APhysicalObject : public AActor, public IDestroyableObject
{
	GENERATED_BODY()

public:
	void TakeDamage(float damage) override;

protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Physical Object")
	void DoDestroy();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Object configuration")
	float condition;

};
