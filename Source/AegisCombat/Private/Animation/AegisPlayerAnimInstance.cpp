// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AegisPlayerAnimInstance.h"
#include "VectorTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAegisPlayerAnimInstance::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<ACharacter>(GetOwningActor());
	if (!PlayerCharacter)
		return;

	MovementComponent = PlayerCharacter->GetCharacterMovement();
}

void UAegisPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!IsValid(PlayerCharacter) || !MovementComponent)
		return;

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Length();

	FVector CurAccel = MovementComponent->GetCurrentAcceleration();
	bShouldMove = 3.f < GroundSpeed && FVector::ZeroVector != CurAccel;
	
	bIsFalling = MovementComponent->IsFalling();
	
	FVector NormalizedVelocity = UE::Geometry::Normalized(Velocity);
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector RightVector = PlayerCharacter->GetActorRightVector();
	
	Forward = UE::Geometry::Dot(NormalizedVelocity, ForwardVector);
	Strafe = UE::Geometry::Dot(NormalizedVelocity, RightVector);
}
