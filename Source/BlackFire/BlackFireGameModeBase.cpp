// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackFireGameModeBase.h"

ABlackFireGameModeBase::ABlackFireGameModeBase()
{
	PlayerControllerClass = ACustomPlayerController::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
}