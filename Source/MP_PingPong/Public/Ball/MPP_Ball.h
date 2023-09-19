// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPP_Ball.generated.h"

UCLASS()
class MP_PINGPONG_API AMPP_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPP_Ball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float fSpeed = 1000.f;

	UPROPERTY(ReplicatedUsing = OnRep_Direction)
	FVector Direction;


	UFUNCTION()
	void OnRep_Direction();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION(Server, Unreliable)
	void UpdateServerTransform(FTransform Transform, float DeltaTime);

	float LocationZ;
	
	UFUNCTION(NetMulticast , Unreliable)
	void UpdateNetMulticastTransform(FTransform Transform, float DeltaTime);
};
