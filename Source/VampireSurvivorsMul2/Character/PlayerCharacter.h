// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FloorCountableInterface.h"
#include "Interface/HpBarInterface.h"
#include "ItemData/ItemDataBase.h"
#include "Interface/CharacterItemInterface.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, UItemDataBase* /*ItemData*/)

USTRUCT()
struct FOnTakeItemDelegateWrapper
{
	GENERATED_BODY()
	
public:
	FOnTakeItemDelegate OnTakeItem;

public:
	FOnTakeItemDelegateWrapper() { ; }
	FOnTakeItemDelegateWrapper(const FOnTakeItemDelegate& InTakeItemDelegate) : OnTakeItem(InTakeItemDelegate) { ; }
};

UCLASS(Blueprintable)
class VAMPIRESURVIVORSMUL2_API APlayerCharacter : public ACharacter, public IFloorCountableInterface, public IHpBarInterface, public ICharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Input Section
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;


// Move Section
public:
	UFUNCTION()
	void HandleMove(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Server_HandleMove(const FVector& MoveDirection);
	void Server_HandleMove_Implementation(const FVector& MoveDirection);

// Health Section
protected:
	UPROPERTY()
	TObjectPtr<class UHealthComponent> HealthComponent;

// HpBar Section
public:
	virtual void InitHpBar(UUserWidget* HpBarWidget) override;

// Damage Section
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

// Item Section
private:
	UPROPERTY()
	TMap<EItemType, FOnTakeItemDelegateWrapper> TakeItemDelegateWrappers;

	virtual void TakeItem(UItemDataBase* ItemData) override;

	void TakeRedBox(UItemDataBase* ItemData);
	void TakeBlueBox(UItemDataBase* ItemData);
	void TakeGreenBox(UItemDataBase* ItemData);
	void TakeHealBox(UItemDataBase* ItemData);

};
