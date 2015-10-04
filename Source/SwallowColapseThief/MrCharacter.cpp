// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "MrCharacter.h"

// Sets default values
AMrCharacter::AMrCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_isChanneling = false;
	m_isCharging = false;

	m_controler = 0;
	m_controlee = 0;

	m_ability = PA_NONE;
}

// Called when the game starts or when spawned
void AMrCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMrCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isCharging)
	{
		ChargeTick();
	}
}

// Called to bind functionality to input
void AMrCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction(TEXT("ActionBasic"), IE_Pressed, this, &AMrCharacter::ActionBasic);
	InputComponent->BindAction(TEXT("ActionSpecial"), IE_Pressed, this, &AMrCharacter::ActionSpecial);
	InputComponent->BindAction(TEXT("ActionSpecial"), IE_Released, this, &AMrCharacter::ActionSpecialReleased);
	InputComponent->BindAxis(TEXT("Movement_X"), this, &AMrCharacter::Movement_X);
	InputComponent->BindAxis(TEXT("Movement_Y"), this, &AMrCharacter::Movement_Y);
	InputComponent->BindAxis(TEXT("Direction_X"), this, &AMrCharacter::Direction_X);
	InputComponent->BindAxis(TEXT("Direction_Y"), this, &AMrCharacter::Direction_Y);
}

void AMrCharacter::ActionBasic()
{
	ChargeStart();
}

void AMrCharacter::ActionSpecial()
{
	m_isChanneling = true;
	switch (m_ability)
	{
	case PA_SWALLOW:
		SwallowStart();
		break;
	case PA_THEIF:
		ChargeStart();
		break;
	case PA_COLLAPSE:
		AttackLevel();
		break;
	}
}

void AMrCharacter::ActionSpecialReleased()
{
	m_isChanneling = false;
}

void AMrCharacter::Movement_X(float value)
{
	if (m_isCharging || (m_ability == PA_SWALLOW && m_isChanneling))
		return;

	GetCharacterMovement()->AddInputVector(FVector(0, 1, 0) * value);
}

void AMrCharacter::Movement_Y(float value)
{
	if (m_isCharging || (m_ability == PA_SWALLOW && m_isChanneling))
		return;

	GetCharacterMovement()->AddInputVector(FVector(1, 0, 0) * value);
}

void AMrCharacter::Direction_X(float value)
{
	const float deltaY = InputComponent->GetAxisValue(TEXT("Direction_Y"));
	FRotator rotation = CalculateRotation(value, deltaY);
	GetController()->SetControlRotation(rotation);
}

void AMrCharacter::Direction_Y(float value)
{
	const float deltaX = InputComponent->GetAxisValue(TEXT("Direction_X"));
	FRotator rotation = CalculateRotation(deltaX, value);
	GetController()->SetControlRotation(rotation);
}

FRotator AMrCharacter::CalculateRotation(float deltaX, float deltaY)
{
	const FRotator rotationCurrent = GetController()->GetControlRotation();
	FRotator result = rotationCurrent;

	FVector directionCurrent = GetController()->GetControlRotation().Vector();
	FVector directionTarget(deltaY, deltaX, 0.0f);

	if (directionTarget != FVector::ZeroVector
		&& directionTarget.SizeSquared() > 0.0f)
	{
		FRotator rotationTarget = directionTarget.Rotation();
		result = FMath::Lerp(rotationCurrent, rotationTarget, 0.1f);
	}

	return result;
}

void AMrCharacter::ChargeStart()
{
	// You can't charge while possessing someone
	if (m_controlee || m_controler)
		return;

	UCharacterMovementComponent* characterMovement = GetCharacterMovement();

	if (GetWorld()->GetTimerManager().GetTimerRemaining(m_chargeCooldownHandle) <= 0.0f)
	{
		m_isCharging = true;

		FVector directionCurrent = GetVelocity();
		if (directionCurrent.SizeSquared() == 0)
			directionCurrent = GetController()->GetControlRotation().Vector();// only boost where we're facing if we're not moving
		directionCurrent.Normalize();
		
		characterMovement->StopActiveMovement();
		characterMovement->AddImpulse(directionCurrent * m_chargeForce, true);
		characterMovement->MovementMode = EMovementMode::MOVE_Flying;

		GetWorld()->GetTimerManager().SetTimer(m_chargeTimeHandle, this, &AMrCharacter::ChargeFinish, m_chargeTime, false);
		GetWorld()->GetTimerManager().SetTimer(m_chargeCooldownHandle, m_chargeCooldown, false);
	}
}

void AMrCharacter::SwallowStart()
{
	GetCharacterMovement()->StopActiveMovement();
}

void AMrCharacter::AttackLevel()
{

}

void AMrCharacter::ChargeFinish()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ChargeFinish");
	m_isCharging = false;

	GetWorld()->GetTimerManager().ClearTimer(m_chargeTimeHandle);

	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
}

int32 AMrCharacter::GetAbility()
{
	return (int32)m_ability;
}

void AMrCharacter::PossessOther(AMrCharacter* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "PossessOther");
	if (m_controlee || m_controler)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Possess success");
	m_controlee = other;
	m_controlee->LoseControl(this);
}

void AMrCharacter::SetSpecialAbility(int32 ability)
{
	m_ability = (PlayerAbility)ability;
}

void AMrCharacter::LoseControl(AMrCharacter* controler)
{
	m_controler = controler;
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
}

void AMrCharacter::ReclaimControl()
{
	if (m_controler)
	{
		m_controler->ReclaimControl();
		m_controler = 0;
	}

	if (m_controlee)
	{
		m_controlee = 0;
	}

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None)
	{
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	}
}