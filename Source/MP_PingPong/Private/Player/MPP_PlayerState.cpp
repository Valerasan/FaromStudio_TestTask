// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPP_PlayerState.h"

FName AMPP_PlayerState::GetPlayerIDName_Implementation()
{
	return PlayerName;
}

void AMPP_PlayerState::AddPlayerScore_Implementation(int32 AddScore)
{
	PlayerScore += AddScore;
}
