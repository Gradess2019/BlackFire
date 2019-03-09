// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerObserver.h"
#include "BlackFire.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "GUI.generated.h"

/**
 * 
 */
UCLASS()
class BLACKFIRE_API UGUI : public UUserWidget, public IPlayerObserver
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "GUI configuration")
	void InitTextBlocks(UTextBlock* currentAmmoInMagazine, UTextBlock* currentAmmo, UTextBlock* healthBar);

	void Update(class IPlayerSubject* subject) override;
	
protected:

	UPROPERTY(BlueprintReadOnly)
	UTextBlock* currentAmmoInMagazineText;

	UPROPERTY(BlueprintReadOnly)
	UTextBlock* currentAmmoText;

	UPROPERTY(BlueprintReadOnly)
	UTextBlock* healthBar;

	bool IsValidTextBlocks();
};
