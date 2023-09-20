// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPP_UserWidget.generated.h"

class UTextBlock;

UCLASS()
class MP_PINGPONG_API UMPP_UserWidget : public UUserWidget
{
	GENERATED_BODY()


private:
	virtual bool Initialize() override;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* OwnScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyScore;
	
public:
	void SetScore(bool Own, int32 Score);
	
};
