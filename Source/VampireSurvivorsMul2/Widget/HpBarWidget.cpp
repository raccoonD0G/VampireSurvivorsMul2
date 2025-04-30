// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Component/HealthComponent.h"
#include "Interface/HpBarInterface.h"

void UHpBarWidget::UpdateHealth(float NewCurrentHealth, float MaxHealth)
{
	if (HpBar && MaxHealth > 0.f)
	{
		const float ClampedHealth = FMath::Clamp(NewCurrentHealth / MaxHealth, 0.f, 1.f);
		HpBar->SetPercent(ClampedHealth);
	}
}

void UHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IHpBarInterface* HpBarInterface = Cast<IHpBarInterface>(OwningActor);
	if (HpBarInterface)
	{
		HpBarInterface->InitHpBar(this);
	}

}


