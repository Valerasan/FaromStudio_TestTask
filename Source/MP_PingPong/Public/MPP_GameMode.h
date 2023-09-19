// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPP_GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "MPP_GameMode.generated.h"

class AMPP_Ball;

UCLASS()
class MP_PINGPONG_API AMPP_GameMode : public AGameModeBase , public IMPP_GameModeInterface
{
	GENERATED_BODY()
	



public:
	AMPP_GameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
						  FString& ErrorMessage) override;
	
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
		const FString& Options, const FString& Portal = TEXT("")) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AMPP_Ball> BallCLass;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool AddPlayerScore(FName PlayerName); virtual bool AddPlayerScore_Implementation(FName PlayerName) override;
	


	
private:
	TArray<class APlayerStart*> FreePlayerStarts;
	TArray<AController*> Players;
	void SpawnBall();

	FTimerHandle SpawnBallTh;


	// UFUNCTION(Server, Reliable)
	// void ServerSpawnBall();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnBall();
};