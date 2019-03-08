// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FirePoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKFIRE_API UFirePoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFirePoint();
	
};
