// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/DungeonPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UObject/ConstructorHelpers.h"
#include "InputMappingContext.h"


ADungeonPlayerController::ADungeonPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Move.IMC_Move'"));
	if (IMCObj.Succeeded())
	{
		MoveMappingContext = IMCObj.Object;
	}
}

void ADungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MoveMappingContext)
		{
			Subsystem->AddMappingContext(MoveMappingContext, 0);
		}
	}
}
