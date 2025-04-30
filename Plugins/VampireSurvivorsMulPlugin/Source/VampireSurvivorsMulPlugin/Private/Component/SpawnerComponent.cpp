// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpawnerComponent.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastSpawn = 0.0f;
}

void USpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->HasAuthority())
	{
		TimeSinceLastSpawn += DeltaTime;
		if (TimeSinceLastSpawn >= SpawnInterval)
		{
			SpawnRandomActor();
			TimeSinceLastSpawn = 0.0f;
		}
	}
}

void USpawnerComponent::SpawnRandomActor()
{
	if (SpawnActorClasses.Num() == 0 || !GetWorld() || !GetOwner()) return;

	if (SpawnedActors.Num() >= MaxSpawnCount) return;

	FVector Origin = GetOwner()->GetActorLocation();

	// NavMesh ���� ��ġ ã��
	FNavLocation ResultLocation;
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSys && NavSys->GetRandomReachablePointInRadius(Origin, SpawnRadius, ResultLocation))
	{
		// ���� Ŭ���� ����
		int32 Index = FMath::RandRange(0, SpawnActorClasses.Num() - 1);
		TSubclassOf<AActor> ChosenClass = SpawnActorClasses[Index];
		if (!ChosenClass) return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnedActors.Add(GetWorld()->SpawnActor<AActor>(ChosenClass, ResultLocation.Location, FRotator::ZeroRotator, SpawnParams));
	}
}


