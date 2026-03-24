// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AegisCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Combat/AegisCombatComponent.h"
#include "Core/AegisLog.h"
#include "Player/AegisPlayerController.h"

// Sets default values
AAegisCharacter::AAegisCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Combat = CreateDefaultSubobject<UAegisCombatComponent>(TEXT("Combat"));

	// Character rotation driven by movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
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
	
	EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAegisCharacter::HandleMove);
	EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AAegisCharacter::HandleLook);
	EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &AAegisCharacter::HandleAttackStarted);
}

void AAegisCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (AAegisPlayerController* PC = Cast<AAegisPlayerController>(GetController()))
	{
		PC->SetRespawnTransform(GetActorTransform());
	}
}

void AAegisCharacter::HandleMove(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (!GetController())
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
	if (!GetController())
		return;
	
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