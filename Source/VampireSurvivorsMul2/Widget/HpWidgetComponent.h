// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ActorOwnableWidgetComponent.h"
#include "HpWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (UI), meta = (BlueprintSpawnableComponent))
class VAMPIRESURVIVORSMUL2_API UHpWidgetComponent : public UActorOwnableWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
	
	
};
