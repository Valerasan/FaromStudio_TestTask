// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/MPP_Ball.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"

AMPP_Ball::AMPP_Ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AMPP_Ball::BeginPlay()
{
	Super::BeginPlay();

	if(GetLocalRole() == ROLE_Authority)
	{
		Direction  = FMath::VRand() * fSpeed;
		LocationZ = GetActorLocation().Z;
		Direction.Z = LocationZ;	
	}
}

// Called every frame
void AMPP_Ball::Tick(float DeltaTime)
{

	if (HasAuthority())
	{
		UpdateServerTransform(GetActorTransform(), DeltaTime);
	}
	FString Rolle = GetLocalRole() == ROLE_SimulatedProxy ? "SimulatedProxy" : "Other";
	//UE_LOG(LogTemp, Warning, TEXT("%s, Location: %s"), *Rolle, *GetTransform().GetLocation().ToString())
}


void AMPP_Ball::OnRep_Direction()
{
	//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());
}

void AMPP_Ball::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION(AMPP_Ball, Direction, COND_InitialOnly);
}

void AMPP_Ball::UpdateNetMulticastTransform_Implementation(FTransform Transform, float DeltaTime)
{
	SetActorTransform(Transform);
}

void AMPP_Ball::UpdateServerTransform_Implementation(FTransform Transform, float DeltaTime)
{

	float Time = GetWorld()->GetDeltaSeconds();

	FVector ActorLocation = GetActorLocation();
	ActorLocation.Z = LocationZ;
	FVector NextLocation = (Direction * fSpeed * Time) + ActorLocation;
	FHitResult hitResult;
	SetActorLocation(NextLocation, true, &hitResult);
	//
	if(hitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), hitResult.ImpactNormal, 5.f, 16, FColor::Red, false , 30.f);
		DrawDebugSphere(GetWorld(), ActorLocation, 5.f, 16, FColor::Green, false , 30.f);
		DrawDebugDirectionalArrow(GetWorld(), hitResult.ImpactNormal, hitResult.ImpactNormal * 100.f, 5, FColor::Red, false , 30.f);
		Direction = FMath::GetReflectionVector(Direction, hitResult.ImpactNormal);
	}
	UpdateNetMulticastTransform(GetActorTransform(), DeltaTime);
}

