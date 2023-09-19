// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPP_BallGoal.generated.h"

class AMPP_GameMode;
class UBoxComponent;
class UPrimitiveComponent;

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

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FName PlayerName;

public:	


private:

	UPROPERTY()
	AMPP_GameMode* GameMode;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);

};
