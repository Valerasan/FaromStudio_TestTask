// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MPP_PlayerStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMPP_PlayerStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MP_PINGPONG_API IMPP_PlayerStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetPlayerIDName();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddPlayerScore(int32 AddScore);

};
