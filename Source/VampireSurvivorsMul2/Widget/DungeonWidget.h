// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API UDungeonWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText;

public:
	void SetCountText(int32 RedCount, int32 GreenCount, int32 BlueCount);
	
};
