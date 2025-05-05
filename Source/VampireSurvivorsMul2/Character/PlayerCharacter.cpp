// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widget/HpBarWidget.h"
#include "Component/HealthComponent.h"
#include "GameMode/DungeonGameMode.h"
#include "ItemData/HealBoxData.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f); //

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	if (MoveActionObj.Succeeded())
	{
		MoveAction = MoveActionObj.Object;
	}

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	TakeItemDelegateWrappers.Add(EItemType::Red, FOnTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &APlayerCharacter::TakeRedBox)));
	TakeItemDelegateWrappers.Add(EItemType::Green, FOnTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &APlayerCharacter::TakeGreenBox)));
	TakeItemDelegateWrappers.Add(EItemType::Blue, FOnTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &APlayerCharacter::TakeBlueBox)));
	TakeItemDelegateWrappers.Add(EItemType::Heal, FOnTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &APlayerCharacter::TakeHealBox)));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		ADungeonGameMode* DungeonGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
		if (DungeonGameMode)
		{
			HealthComponent->OnHealthZero.AddUObject(DungeonGameMode, &ADungeonGameMode::SetLose);
			
		}
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMove);
	}

}


void APlayerCharacter::HandleMove(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();

	if (MoveInput.IsNearlyZero())
	{
		return;
	}

	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.f;
	CameraRotation.Roll = 0.f;

	FVector Forward = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MoveInput.Y);
	AddMovementInput(Right, MoveInput.X);

	FVector MoveDirection = (Forward * MoveInput.Y + Right * MoveInput.X).GetSafeNormal();

	Server_HandleMove(MoveDirection);

	if (MoveDirection.IsNearlyZero())
	{
		return;
	}

	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = MoveDirection.Rotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	SetActorRotation(NewRotation);
}

void APlayerCharacter::Server_HandleMove_Implementation(const FVector& MoveDirection)
{
	
}

void APlayerCharacter::InitHpBar(UUserWidget* HpBarWidget)
{
	UHpBarWidget* HpBar = Cast<UHpBarWidget>(HpBarWidget);
	HealthComponent->OnHealthChanged.AddUObject(HpBar, &UHpBarWidget::UpdateHealth);
	HealthComponent->OnHealthChanged.Broadcast(HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HealthComponent->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return DamageAmount;
}

void APlayerCharacter::TakeItem(UItemDataBase* ItemData)
{
	TakeItemDelegateWrappers[ItemData->ItemType].OnTakeItem.Execute(ItemData);
}

void APlayerCharacter::TakeRedBox(UItemDataBase* ItemData)
{
	ADungeonGameMode* DungeonGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
	if (DungeonGameMode)
	{
		DungeonGameMode->AddRedBoxCount();
	}
}

void APlayerCharacter::TakeBlueBox(UItemDataBase* ItemData)
{
	ADungeonGameMode* DungeonGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
	if (DungeonGameMode)
	{
		DungeonGameMode->AddBlueBoxCount();
	}
}

void APlayerCharacter::TakeGreenBox(UItemDataBase* ItemData)
{
	ADungeonGameMode* DungeonGameMode = Cast<ADungeonGameMode>(GetWorld()->GetAuthGameMode());
	if (DungeonGameMode)
	{
		DungeonGameMode->AddGreenBoxCount();
	}
}

void APlayerCharacter::TakeHealBox(UItemDataBase* ItemData)
{
	UHealBoxData* HealBoxData = Cast<UHealBoxData>(ItemData);
	HealthComponent->HealHealth(HealBoxData->HealAmount);
}
