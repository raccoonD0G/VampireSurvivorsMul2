// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData/ItemBox.h"
#include "Interface/CharacterItemInterface.h"
#include "Engine/AssetManager.h"
#include "ItemData/ItemDataBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetIsReplicated(true);
	RootComponent = Mesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetIsReplicated(true);
	Trigger->SetupAttachment(Mesh);

	bReplicates = true;
}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (HasAuthority())
	{
		ICharacterItemInterface* CharacterItemInterface = Cast<ICharacterItemInterface>(OtherActor);
		if (CharacterItemInterface)
		{
			CharacterItemInterface->TakeItem(ItemData);
			Destroy();
		}
	}
}

