// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AegisCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Combat/AegisCombatComponent.h"
#include "Core/AegisLog.h"

// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 350.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	Combat = CreateDefaultSubobject<UAegisCombatComponent>(TEXT("Combat"));

	// Character rotation driven by movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
}

// Called to bind functionality to input
void AAegisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EIC)
	{
		UE_LOG(LogAegis, Error, TEXT("EnhancedInputComponent missing"));
		return;
	}

	if (IA_Move)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAegisCharacter::HandleMove);
	}
	else
	{
		UE_LOG(LogAegis, Warning, TEXT("IA_Move not set"));
	}

	if (IA_Look)
	{
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAegisCharacter::HandleLook);
	}
	else
	{
		UE_LOG(LogAegis, Warning, TEXT("IA_Look not set"));
	}

	if (IA_Attack)
	{
		EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &AAegisCharacter::HandleAttackStarted);
	}
	else
	{
		UE_LOG(LogAegis, Warning, TEXT("IA_Attack not set"));
	}
}

void AAegisCharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (!Controller)
		return;

	const FRotator ControlRot = Controller->GetControlRotation();
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Axis.Y);
	AddMovementInput(Right, Axis.X);
}

void AAegisCharacter::HandleLook(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(-Axis.Y);
}

void AAegisCharacter::HandleAttackStarted(const FInputActionValue& Value)
{
	if (!Combat)
	{
		UE_LOG(LogAegisCombat, Error, TEXT("CombatComponent missing"));
		return;
	}

	const bool bStarted = Combat->TryStartAttack();
	UE_LOG(LogAegisCombat, Log, TEXT("Attack Pressed -> TryStartAttack = %s"), bStarted ? TEXT("true") : TEXT("false"));
}