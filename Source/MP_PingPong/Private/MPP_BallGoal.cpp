// Fill out your copyright notice in the Description page of Project Settings.


#include "MPP_BallGoal.h"

#include "MPP_GameMode.h"
#include "MPP_GameModeInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMPP_BallGoal::AMPP_BallGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	
}

// Called when the game starts or when spawned
void AMPP_BallGoal::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMPP_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMPP_BallGoal::OnBeginOverlap);
	
}

void AMPP_BallGoal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	if(HasAuthority())
	{
		if(!GameMode)
			return;

		GameMode->DestroyBall();
		IMPP_GameModeInterface::Execute_AddPlayerScore(GameMode, PlayerName);
	}
}



