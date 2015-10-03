// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "MrCharacter.h"


// Sets default values
AMrCharacter::AMrCharacter() :
	m_yaw(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMrCharacter::BeginPlay()
{
	Super::BeginPlay();
	InputComponent->BindAction(TEXT("ActionBasic"), IE_Pressed, this, &AMrCharacter::ActionBasic);
	InputComponent->BindAction(TEXT("ActionSpecial"), IE_Pressed, this, &AMrCharacter::ActionSpecial);
	InputComponent->BindAxis(TEXT("Movement_X"), this, &AMrCharacter::Movement_X);
	InputComponent->BindAxis(TEXT("Movement_Y"), this, &AMrCharacter::Movement_Y);
	InputComponent->BindAxis(TEXT("Direction_X"), this, &AMrCharacter::Direction_X);
	InputComponent->BindAxis(TEXT("Direction_Y"), this, &AMrCharacter::Direction_Y);
}

// Called every frame
void AMrCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator rotationCurrent = GetActorRotation();
	if (rotationCurrent.Yaw != m_yaw)
	{
		GetController()->SetControlRotation(FRotator(0.0f, m_yaw, 0.0f));
	}

}

// Called to bind functionality to input
void AMrCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMrCharacter::ActionBasic()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ActionBasic");
}

void AMrCharacter::ActionSpecial()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ActionSpecial");
}

void AMrCharacter::Movement_X(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Movement_X");
	CharacterMovement->AddInputVector(FVector(0, 1, 0) * value);
}

void AMrCharacter::Movement_Y(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Movement_Y");
	CharacterMovement->AddInputVector(FVector(1, 0, 0) * value);
}

void AMrCharacter::Direction_X(float value)
{
	if (value != 0.0f)
	{
		const float deltaY = InputComponent->GetAxisValue(TEXT("Direction_Y"));
		m_yaw = GetRotationYaw(value, deltaY);
	}
}

void AMrCharacter::Direction_Y(float value)
{
	if (value != 0.0f)
	{
		const float deltaX = InputComponent->GetAxisValue(TEXT("Direction_X"));
		m_yaw = GetRotationYaw(deltaX, value);
	}
}

float AMrCharacter::GetRotationYaw(float deltaX, float deltaY)
{
	FVector direction(deltaY, deltaX, 0.0f);
	direction.Normalize();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, direction.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, direction.Rotation().ToString());
	
	return direction.Rotation().Yaw;
}