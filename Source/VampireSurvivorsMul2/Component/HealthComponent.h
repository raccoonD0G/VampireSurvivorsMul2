// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float /*NewCurrentHealth*/, float /*CurrentMaxHealth*/);
DECLARE_MULTICAST_DELEGATE(FOnHealthZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVORSMUL2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	FOnHealthChangedDelegate OnHealthChanged;
	FOnHealthZeroDelegate OnHealthZero;

	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE void SetCurrentHealth(float NewCurrentHealth)
	{
		CurrentHealth = FMath::Clamp(NewCurrentHealth, 0, MaxHealth);
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
		if (CurrentHealth < KINDA_SMALL_NUMBER)
		{
			OnHealthZero.Broadcast();
		}
	}

private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

private:
	UFUNCTION()
	void OnRep_CurrentHealth();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	void HealHealth(float HealAmount);
};
