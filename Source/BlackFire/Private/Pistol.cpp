// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistol.h"

APistol::APistol()
{
	currentAmmoInMagazine = 10;
	maxAmmoInMagazine = 10;
	currentAmmo = 50;
	maxAmmo = 50;

	damage = 15;
	reloadingTime = 1.f;
	fireRate = 240;
}