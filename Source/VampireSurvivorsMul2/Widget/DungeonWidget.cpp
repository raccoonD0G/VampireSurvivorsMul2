// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DungeonWidget.h"
#include "Components/TextBlock.h"
#include "GameState/DungeonGameState.h"

void UDungeonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ADungeonGameState* DungeonGameState = Cast<ADungeonGameState>(GetWorld()->GetGameState());
	if (DungeonGameState)
	{
		DungeonGameState->OnBoxCountChange.AddUObject(this, &UDungeonWidget::SetCountText);
	}
}

void UDungeonWidget::SetCountText(int32 RedCount, int32 GreenCount, int32 BlueCount)
{
	if (CountText)
	{
		FString FormattedString = FString::Printf(TEXT("Red : %d | Green : %d | Blue : %d"), RedCount, GreenCount, BlueCount);
		CountText->SetText(FText::FromString(FormattedString));
	}
}
