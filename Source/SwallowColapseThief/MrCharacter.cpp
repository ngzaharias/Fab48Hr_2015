// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "MrCharacter.h"


// Sets default values
AMrCharacter::AMrCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	
}

// Called to bind functionality to input
void AMrCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction(TEXT("ActionBasic"), IE_Pressed, this, &AMrCharacter::ActionBasic);
	InputComponent->BindAction(TEXT("ActionSpecial"), IE_Pressed, this, &AMrCharacter::ActionSpecial);
	InputComponent->BindAxis(TEXT("Movement_X"), this, &AMrCharacter::Movement_X);
	InputComponent->BindAxis(TEXT("Movement_Y"), this, &AMrCharacter::Movement_Y);
	InputComponent->BindAxis(TEXT("Direction_X"), this, &AMrCharacter::Direction_X);
	InputComponent->BindAxis(TEXT("Direction_Y"), this, &AMrCharacter::Direction_Y);
}

void AMrCharacter::ActionBasic()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ActionBasic");

	ChargeStart();
}

void AMrCharacter::ActionSpecial()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ActionSpecial");
}

void AMrCharacter::Movement_X(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Movement_X");
	GetCharacterMovement()->AddInputVector(FVector(0, 1, 0) * value);
}

void AMrCharacter::Movement_Y(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Movement_Y");
	GetCharacterMovement()->AddInputVector(FVector(1, 0, 0) * value);
}

void AMrCharacter::Direction_X(float value)
{
	const float deltaY = InputComponent->GetAxisValue(TEXT("Direction_Y"));
	FRotator rotation = CalculateRotation(value, deltaY);
	GetController()->SetControlRotation(rotation);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Direction_X");
}

void AMrCharacter::Direction_Y(float value)
{
	const float deltaX = InputComponent->GetAxisValue(TEXT("Direction_X"));
	FRotator rotation = CalculateRotation(deltaX, value);
	GetController()->SetControlRotation(rotation);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Direction_Y");
}

FRotator AMrCharacter::CalculateRotation(float deltaX, float deltaY)
{
	FVector directionCurrent = GetController()->GetControlRotation().Vector();
	FVector directionTarget(deltaY, deltaX, 0.0f);

	if (directionTarget != FVector::ZeroVector
		&& directionTarget.SizeSquared() > 0.0f)
	{
		FRotator rotationCurrent = GetController()->GetControlRotation();
		FRotator rotationTarget = directionTarget.Rotation();
		return FMath::Lerp(rotationCurrent, rotationTarget, 0.1f);
	}

	return FRotator::ZeroRotator;
}

void AMrCharacter::ChargeStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ChargeStart");

	FVector directionCurrent = GetController()->GetControlRotation().Vector();
	GetCharacterMovement()->AddImpulse(directionCurrent * m_chargeForce);

	GetWorld()->GetTimerManager().SetTimer(m_chargeTimerHandle, this, &AMrCharacter::ChargeFinish, 1.0f, false);
}

void AMrCharacter::ChargeFinish()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ChargeFinish");
}