// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::InitializeHealth(float InMaxHealth, float InCurrentHealth)
{
	MaxHealth = FMath::Max(1.0f, InMaxHealth);
	CurrentHealth = FMath::Clamp(InCurrentHealth, 0.0f, MaxHealth);
	bIsDead = (CurrentHealth <= 0.0f);
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	if (bIsDead || DamageAmount <= 0.0f)
	{
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	if (CurrentHealth <= 0.0f)
	{
		bIsDead = true;
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.0f || bIsDead)
	{
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
}





