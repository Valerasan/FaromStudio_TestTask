// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MPP_Player.generated.h"

class UMPP_UserWidget;

UCLASS()
class MP_PINGPONG_API AMPP_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMPP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverRight(float Value);

	UFUNCTION()
	void UpdateScore(int32 Score);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UMPP_UserWidget> PlayerHUDClass;

	UPROPERTY()
	UMPP_UserWidget* PlayerHUD;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	float Speed = 200.f;

private:

	/** Update server with latest transform from the client. */
	UFUNCTION(Server, Unreliable)
	void UpdateServerTransform(FTransform Transform);


};