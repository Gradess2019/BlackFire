// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ETeam : uint8
{
	None,
	Blue,
	Red
};

UENUM()
enum class EShootingMode : uint8
{
	Single,
	SemiAuto,
	Auto
};