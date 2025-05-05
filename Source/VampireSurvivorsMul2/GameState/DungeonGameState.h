// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnBoxCountChangeDelegate, int32 /*RedBoxCount*/, int32 /*GreenBoxCount*/, int32 /*BlueBoxCount*/)

UENUM()
enum class EGameState : uint8
{
	OnGoing,
	Win,
	Lose
};
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API ADungeonGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ADungeonGameState();

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	FORCEINLINE void SetRedBoxCount(int32 NewRedBoxCount) { RedBoxCount = NewRedBoxCount; OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount); }
	FORCEINLINE void SetGreenBoxCount(int32 NewGreenBoxCount) { GreenBoxCount = NewGreenBoxCount; OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount);}
	FORCEINLINE void SetBlueBoxCount(int32 NewBlueBoxCount) { BlueBoxCount = NewBlueBoxCount; OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount);}

	FOnBoxCountChangeDelegate OnBoxCountChange;

private:
	UPROPERTY(ReplicatedUsing = OnRep_RedBoxCount)
	int32 RedBoxCount;

	UPROPERTY(ReplicatedUsing = OnRep_GreenBoxCount)
	int32 GreenBoxCount;

	UPROPERTY(ReplicatedUsing = OnRep_BlueBoxCount)
	int32 BlueBoxCount;

private:
	UFUNCTION()
	void OnRep_RedBoxCount();

	UFUNCTION()
	void OnRep_GreenBoxCount();

	UFUNCTION()
	void OnRep_BlueBoxCount();

// State Section
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CurrentState)
	EGameState CurrentState = EGameState::OnGoing;

	UFUNCTION()
	void OnRep_CurrentState();

public:
	FORCEINLINE EGameState GetCurrentState() const { return CurrentState; }
	void SetCurrentState(EGameState NewState);

};
