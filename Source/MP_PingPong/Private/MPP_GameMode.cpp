// Fill out your copyright notice in the Description page of Project Settings.


#include "MPP_GameMode.h"
#include "EngineUtils.h"
#include "Ball/MPP_Ball.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MPP_PlayerState.h"

AMPP_GameMode::AMPP_GameMode()
{
}
void AMPP_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogTemp, Warning, TEXT("Game is running: %s %s"), *MapName, *Options);

}

void AMPP_GameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		FreePlayerStarts.Add(*It);
		UE_LOG(LogTemp, Warning, TEXT("Found player start: %s"), *(*It)->GetName());
	}
}

void AMPP_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMPP_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	FString& ErrorMessage)
{
	if (FreePlayerStarts.Num() == 0)
	{
		ErrorMessage = TEXT("Server full");
		UE_LOG(LogTemp, Warning, TEXT("Server full"));
	}

	
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

FString AMPP_GameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	const FString& Options, const FString& Portal)
{
	if (FreePlayerStarts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No free player starts in InitNewPlayer"));
		return FString(TEXT("No free player starts"));
	}

	APlayerStart* PlayerStart = FreePlayerStarts.Pop();
	NewPlayerController->StartSpot = PlayerStart;
	AMPP_PlayerState* PlayerState = Cast<AMPP_PlayerState>(NewPlayerController->PlayerState);
	if(PlayerState)
	{
		PlayerState->PlayerName = PlayerStart->PlayerStartTag;
		UE_LOG(LogTemp, Warning, TEXT("Using player start %s for %s"),
	*NewPlayerController->StartSpot->GetName(), *NewPlayerController->GetName());
	}


	if(FreePlayerStarts.Num() == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnBallTh, this, &AMPP_GameMode::SpawnBall, 10.f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wait Player"));
	}
	Players.Add(NewPlayerController);
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

bool AMPP_GameMode::AddPlayerScore_Implementation(FName PlayerName)
{
	for (auto Element : Players)
	{
		// auto * PlayerState = Cast<AMPP_PlayerState>(Element->PlayerState);
		// if(PlayerState->)
		//
		// PlayerState->PlayerScore++;
		if(Element->PlayerState->GetClass()->ImplementsInterface(UMPP_PlayerStateInterface::StaticClass()) &&
			IMPP_PlayerStateInterface::Execute_GetPlayerIDName(Element->PlayerState) == PlayerName)
		{
			IMPP_PlayerStateInterface::Execute_AddPlayerScore(Element->PlayerState, 1);
		}
	}
	return false;
}



void AMPP_GameMode::SpawnBall()
{
	MulticastSpawnBall();
}

// void AMPP_GameMode::ServerSpawnBall_Implementation()
// {
// 	MulticastSpawnBall();
// }

void AMPP_GameMode::MulticastSpawnBall_Implementation()
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor(BallCLass, &FVector::ZeroVector);
}