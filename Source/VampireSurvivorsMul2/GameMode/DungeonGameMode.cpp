// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameMode.h"
#include "GameState/DungeonGameState.h"

void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonGameMode::CheckAndSetWin()
{
	if (RedBoxCount >= 3 && GreenBoxCount >= 3 && BlueBoxCount >= 3)
	{
		ADungeonGameState* DungeonGameState = GetGameState<ADungeonGameState>();
		if (DungeonGameState)
		{
			DungeonGameState->SetCurrentState(EGameState::Win);
		}
	}
}

void ADungeonGameMode::SetLose()
{
	ADungeonGameState* DungeonGameState = GetGameState<ADungeonGameState>();
	if (DungeonGameState)
	{
		DungeonGameState->SetCurrentState(EGameState::Lose);
	}
}

void ADungeonGameMode::AddRedBoxCount()
{
	if (RedBoxCount < 3)
	{
		RedBoxCount++;
		CheckAndSetWin();
		ADungeonGameState* DungeonGameState = GetGameState<ADungeonGameState>();
		if (DungeonGameState)
		{
			DungeonGameState->SetRedBoxCount(RedBoxCount);
		}
	}
}

void ADungeonGameMode::AddGreenBoxCount()
{
	if (GreenBoxCount < 3)
	{
		GreenBoxCount++;
		CheckAndSetWin();
		ADungeonGameState* DungeonGameState = GetGameState<ADungeonGameState>();
		if (DungeonGameState)
		{
			DungeonGameState->SetGreenBoxCount(GreenBoxCount);
		}
	}
}

void ADungeonGameMode::AddBlueBoxCount()
{
	if (BlueBoxCount < 3)
	{
		BlueBoxCount++;
		CheckAndSetWin();
		ADungeonGameState* DungeonGameState = GetGameState<ADungeonGameState>();
		if (DungeonGameState)
		{
			DungeonGameState->SetBlueBoxCount(BlueBoxCount);
		}
	}
}

void ADungeonGameMode::PauseGame()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (APlayerController* PC = Iterator->Get())
		{
			SetPause(PC);
		}
	}
}