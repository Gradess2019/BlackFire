// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKFIRE_API UWeaponPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponPoint();
		
};
