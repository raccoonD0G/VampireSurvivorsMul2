// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DungeonHUD.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API ADungeonHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDungeonWidget> DungeonWidgetClass;

	UPROPERTY()
	TObjectPtr<class UDungeonWidget> DungeonWidget;

// Game State Section
public:
	void ShowWinWidget();
	void ShowLoseWidget();
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> WinWidgetClass;

	UPROPERTY()
	TObjectPtr<class UUserWidget> WinWidget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LoseWidgetClass;

	UPROPERTY()
	TObjectPtr<class UUserWidget> LoseWidget;
};

