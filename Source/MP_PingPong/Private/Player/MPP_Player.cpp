// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPP_Player.h"

#include "MPP_UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MPP_Controller.h"
#include "Player/MPP_PlayerState.h"

// Sets default values
AMPP_Player::AMPP_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxComponent;

	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
	
	
}

void AMPP_Player::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && PlayerHUDClass)
	{
		AMPP_Controller* PlayerController = GetController<AMPP_Controller>();
		
		if(!PlayerController) return;
		PlayerHUD = CreateWidget<UMPP_UserWidget>(PlayerController, PlayerHUDClass);
		
		if(!PlayerHUD) return;
		PlayerHUD->AddToPlayerScreen();

		// if(PlayerController->State)
		// {
		// 	PlayerController->State->OnScoreUpdateState.AddDynamic(this, &AMPP_Player::UpdateScore);
		// }
		
	}
	
	// AMPP_Controller* PlayerController = GetController<AMPP_Controller>();
	// if(PlayerController)
	// {
	// 	if(PlayerController->State)
	// 		PlayerController->State->OnScoreUpdateState.AddDynamic(this, &AMPP_Player::UpdateScore);
	// }


	
}

void AMPP_Player::MoverRight(float Value)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.Y = Speed * Value * UGameplayStatics::GetWorldDeltaSeconds(this);
	FHitResult HitResult;
	AddActorLocalOffset(DeltaLocation, true, &HitResult);
}

void AMPP_Player::UpdateScore(int32 Score)
{
	if(IsLocallyControlled())
	{
		PlayerHUD->SetScore(true, Score);
	}
	else
	{
		PlayerHUD->SetScore(false, Score);
	}
}

// Called every frame
void AMPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		UpdateServerTransform(GetTransform());
	}
}

// Called to bind functionality to input
void AMPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMPP_Player::MoverRight);

}

void AMPP_Player::UpdateServerTransform_Implementation(FTransform Transform)
{
	SetActorTransform(Transform);
}



