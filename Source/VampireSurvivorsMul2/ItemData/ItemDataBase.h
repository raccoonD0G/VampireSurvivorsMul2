// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataBase.generated.h"

UENUM()
enum class EItemType : uint8
{
	Red,
	Green,
	Blue,
	Heal
};
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API UItemDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("ItemAsset", GetFName());
	}

public:
	UPROPERTY(EditAnywhere)
	EItemType ItemType;
};
