// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPP_BallGoal.generated.h"

class AMPP_GameMode;
class UBoxComponent;

UCLASS()
class MP_PINGPONG_API AMPP_BallGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPP_BallGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UBoxComponent* BoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	UPROPERTY()
	AMPP_GameMode* GameMode;

};
