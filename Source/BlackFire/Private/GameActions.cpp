// Fill out your copyright notice in the Description page of Project Settings.

#include "GameActions.h"

void IGameActions::DropWeapon(AWeaponActor* weapon)
{
	controlledPawn->GetWeaponSet()->Remove(weapon);
}