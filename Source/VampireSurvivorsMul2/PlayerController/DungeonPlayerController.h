// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API ADungeonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADungeonPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> MoveMappingContext;
	
};
