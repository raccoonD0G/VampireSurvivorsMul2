// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/DungeonGameState.h"
#include "Net/UnrealNetwork.h"
#include "HUD/DungeonHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DungeonGameMode.h"

ADungeonGameState::ADungeonGameState()
{
	bReplicates = true;
}

void ADungeonGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADungeonGameState, RedBoxCount);
	DOREPLIFETIME(ADungeonGameState, GreenBoxCount);
	DOREPLIFETIME(ADungeonGameState, BlueBoxCount);
	DOREPLIFETIME(ADungeonGameState, CurrentState);
}

void ADungeonGameState::OnRep_RedBoxCount()
{
	OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount);
}

void ADungeonGameState::OnRep_GreenBoxCount()
{
	OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount);
}

void ADungeonGameState::OnRep_BlueBoxCount()
{
	OnBoxCountChange.Broadcast(RedBoxCount, GreenBoxCount, BlueBoxCount);
}

void ADungeonGameState::OnRep_CurrentState()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ADungeonHUD* HUD = Cast<ADungeonHUD>(PlayerController->GetHUD()))
	{
		if (CurrentState == EGameState::Win)
		{
			HUD->ShowWinWidget();
		}
		else if (CurrentState == EGameState::Lose)
		{
			HUD->ShowLoseWidget();
		}
	}

	if (HasAuthority())
	{
		ADungeonGameMode* DungeonGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, DungeonGameMode, &ADungeonGameMode::PauseGame, 0.1f, false);
	}
}

void ADungeonGameState::SetCurrentState(EGameState NewState)
{
	CurrentState = NewState;
	OnRep_CurrentState();
}