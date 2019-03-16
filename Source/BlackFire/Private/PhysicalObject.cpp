// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicalObject.h"

void APhysicalObject::TakeDamage(float damage)
{
	condition -= damage;
	if (condition <= 0.f)
	{
		DoDestroy();
	}
}

void APhysicalObject::DoDestroy_Implementation()
{
	Destroy();
}
