// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomNPCController.h"

void ACustomNPCController::BeginPlay()
{
	controlledPawn = Cast<ACustomCharacter>(GetPawn());
}

void ACustomNPCController::Client_StartAttack()
{

}

void ACustomNPCController::Client_StopAttack()
{

}

void ACustomNPCController::Client_Reload()
{

}
