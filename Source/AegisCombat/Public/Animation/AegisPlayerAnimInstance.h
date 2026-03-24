// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AegisPlayerAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class AEGISCOMBAT_API UAegisPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TObjectPtr<ACharacter> PlayerCharacter = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	float GroundSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	float MovementDirection = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	FRotator PreviouseRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	bool bShouldMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential Movement Data")
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Forward = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strafe = 0.f;
};
