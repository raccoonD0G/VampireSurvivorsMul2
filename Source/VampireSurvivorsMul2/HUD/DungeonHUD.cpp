// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DungeonHUD.h"
#include "Widget/DungeonWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ADungeonHUD::BeginPlay()
{
	Super::BeginPlay();

	if (DungeonWidgetClass)
	{
		DungeonWidget = CreateWidget<UDungeonWidget>(GetWorld(), DungeonWidgetClass);
		if (DungeonWidget)
		{
			DungeonWidget->AddToViewport();
		}
	}
}

void ADungeonHUD::ShowWinWidget()
{
	if (!WinWidget && WinWidgetClass)
	{
		WinWidget = CreateWidget<UUserWidget>(GetWorld(), WinWidgetClass);
		if (WinWidget)
		{
			WinWidget->AddToViewport();
		}
	}
}

void ADungeonHUD::ShowLoseWidget()
{
	if (!LoseWidget && LoseWidgetClass)
	{
		LoseWidget = CreateWidget<UUserWidget>(GetWorld(), LoseWidgetClass);
		if (LoseWidget)
		{
			LoseWidget->AddToViewport();
		}
	}
}
