// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPP_Controller.h"

#include "Player/MPP_PlayerState.h"

void AMPP_Controller::BeginPlay()
{
	Super::BeginPlay();

	State = GetPlayerState<AMPP_PlayerState>();
}

void AMPP_Controller::AddScore()
{
	
	OnScoreUpdate.Broadcast(++State->PlayerScore);
}
