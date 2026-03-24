// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AegisHealthComponent.generated.h"

class UAegisHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FAegisHealthChangedSignature,
	UAegisHealthComponent*, HealthComponent,
	float, OldHealth,
	float, NewHealth,
	float, Delta
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AEGISCOMBAT_API UAegisHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAegisHealthComponent();

public:
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetToMax();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float Amount);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;

private:
	void SetHealth_Internal(float NewHealth);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Health")
	float Health = 100.f;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FAegisHealthChangedSignature OnHealthChanged;
};
