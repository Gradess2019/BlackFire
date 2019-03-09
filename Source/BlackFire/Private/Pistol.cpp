// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistol.h"

APistol::APistol()
{
	data.currentAmmoInMagazine = 10;
	data.maxAmmoInMagazine = 10;
	data.currentAmmo = 50;
	data.maxAmmo = 50;

	data.damage = 15;
	data.reloadingTime = 1.f;
	data.fireRate = 240;

	data.mode = EShootingMode::Auto;
}