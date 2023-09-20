// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPP_PlayerStateInterface.h"
#include "GameFramework/PlayerState.h"
#include "MPP_PlayerState.generated.h"


 
UCLASS()
class MP_PINGPONG_API AMPP_PlayerState : public APlayerState , public IMPP_PlayerStateInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Replicated)
	FName PlayerName;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PlayerScore)
	int32 PlayerScore = 0;
	
	UFUNCTION()
	void OnRep_PlayerScore();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FName GetPlayerIDName(); virtual FName GetPlayerIDName_Implementation() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddPlayerScore(int32 AddScore); virtual void AddPlayerScore_Implementation(int32 AddScore) override;
	
};
