// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOMATION_LAB_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Basic Initiation for testing
	void InitializeHealth(float InMaxHealth, float InCurrentHealth);

	// Health Actions
	void TakeDamage(float DamageAmount);
	void Heal(float HealAmount);

	// Getters
	float GetCurrentHealth() const {return CurrentHealth;}
	float GetMaxHealth() const { return MaxHealth; }
	bool GetIsDead() const { return bIsDead; } 

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth = 100.0f;

	bool bIsDead = false;
	
};
