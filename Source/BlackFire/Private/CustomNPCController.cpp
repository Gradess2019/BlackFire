// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomNPCController.h"

void ACustomNPCController::BeginPlay()
{
	controlledPawn = Cast<ACustomCharacter>(GetPawn());
}

void ACustomNPCController::StartAttack()
{

}

void ACustomNPCController::StopAttack()
{

}

void ACustomNPCController::Reload()
{

}
