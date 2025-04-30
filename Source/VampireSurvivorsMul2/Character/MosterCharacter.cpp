// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MosterCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AMosterCharacter::AMosterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
}

// Called when the game starts or when spawned
void AMosterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMosterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMosterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

