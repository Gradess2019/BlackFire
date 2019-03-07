// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistol.h"

APistol::APistol()
{
	currentAmmo = 7;
	maxAmmoInMagazine = 7;
	maxAmmo = 49;
	damage = 15.f;
	reloadingTime = 1.5f;
	fireRate = 120.f;
}