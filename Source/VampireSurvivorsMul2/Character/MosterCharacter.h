// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "interface/DetectServiceInterface.h"
#include "MosterCharacter.generated.h"

UCLASS()
class VAMPIRESURVIVORSMUL2_API AMosterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMosterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// DamageSection
private:
	UPROPERTY()
	TObjectPtr<class USphereComponent> AttackSphere;
};
