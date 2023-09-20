// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPP_PlayerState.h"

#include "Net/UnrealNetwork.h"



void AMPP_PlayerState::OnRep_PlayerScore()
{
}

void AMPP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AMPP_PlayerState, PlayerScore);
	DOREPLIFETIME(AMPP_PlayerState, PlayerName);
}

FName AMPP_PlayerState::GetPlayerIDName_Implementation()
{
	return PlayerName;
}

void AMPP_PlayerState::AddPlayerScore_Implementation(int32 AddScore)
{
	PlayerScore += AddScore;
}
