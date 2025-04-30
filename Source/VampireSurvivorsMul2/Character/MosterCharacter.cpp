// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MosterCharacter.h"
#include "Components/SphereComponent.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMosterCharacter::AMosterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(RootComponent);
}

void AMosterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AttackSphere)
	{
		AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AMosterCharacter::OnAttackOverlapBegin);
		AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AMosterCharacter::OnAttackOverlapEnd);
	}
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

void AMosterCharacter::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		CurrentTarget = Player;

		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &AMosterCharacter::DealDamage, 1.0f, true, 0.0f);
	}
}

void AMosterCharacter::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentTarget)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		CurrentTarget = nullptr;
	}
}

void AMosterCharacter::DealDamage()
{
	if (CurrentTarget && !CurrentTarget->IsPendingKill())
	{
		UGameplayStatics::ApplyDamage(CurrentTarget, 1.f, GetController(), this, nullptr);
	}
}

