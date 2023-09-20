// Fill out your copyright notice in the Description page of Project Settings.


#include "MPP_UserWidget.h"

#include <string>

#include "Components/TextBlock.h"


bool UMPP_UserWidget::Initialize()
{
	Super::Initialize();
	
	OwnScore->SetText(FText::AsNumber(0));
	EnemyScore->SetText(FText::AsNumber(0));
	
	return true;
}

void UMPP_UserWidget::SetScore(bool Own, int32 Score)
{
	if(Own)
		OwnScore->SetText(FText::AsNumber(Score));
	else
		EnemyScore->SetText(FText::AsNumber(Score));

}
