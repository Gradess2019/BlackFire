// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI.h"
#include "PlayerSubject.h"

void UGUI::InitTextBlocks(UTextBlock* currentAmmoInMagazine, UTextBlock* currentAmmo, UTextBlock* healthBar)
{
	currentAmmoInMagazineText = currentAmmoInMagazine;
	currentAmmoText = currentAmmo;
	this->healthBar = healthBar;
}

void UGUI::Update(IPlayerSubject* subject)
{
	if (subject && IsValidTextBlocks())
	{
		FWeaponData weaponData = subject->GetWeaponData();

		FText newAmmoInMagazine = FText::FromString(FString::FromInt(weaponData.currentAmmoInMagazine));
		currentAmmoInMagazineText->SetText(newAmmoInMagazine);

		FText newAmmo = FText::FromString(FString::FromInt(weaponData.currentAmmo));
		currentAmmoText->SetText(newAmmo);
	}
}

bool UGUI::IsValidTextBlocks()
{
	const FString errorMsg = "is null! Check call InitTextBlocks() function in your blueprint\n";
	bool hasError = false;
	if (!currentAmmoInMagazineText)
	{
		UE_LOG(LogTemp, Error, TEXT("currentAmmoInMagazineText %s\n %s\n %s\n %d"), *errorMsg,
			*(FString(__FILE__)), *(FString(__FUNCTION__)), __LINE__);
		hasError = true;
	}
	
	if (!currentAmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("currentAmmoText %s\n %s\n %s\n %d"), *errorMsg,
			*(FString(__FILE__)), *(FString(__FUNCTION__)), __LINE__);
		hasError = true;
	}
	
	if (!healthBar)
	{
		UE_LOG(LogTemp, Error, TEXT("healthBar %s\n %s\n %s\n %d"), *errorMsg,
			*(FString(__FILE__)), *(FString(__FUNCTION__)), __LINE__);
		hasError = true;
	}

	return !hasError;
}