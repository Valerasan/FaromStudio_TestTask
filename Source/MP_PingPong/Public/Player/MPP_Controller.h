// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPP_Controller.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdate, int32, NewScore);

class AMPP_PlayerState;
/**
 * 
 */
UCLASS()
class MP_PINGPONG_API AMPP_Controller : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void AddScore();

	FOnScoreUpdate OnScoreUpdate;
	AMPP_PlayerState* State;
};
