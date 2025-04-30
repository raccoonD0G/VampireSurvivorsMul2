// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ActorOwnableUserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API UHpBarWidget : public UActorOwnableUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float NewCurrentHealth, float MaxHealth);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpBar;
};