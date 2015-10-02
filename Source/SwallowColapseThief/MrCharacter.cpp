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
void AMrCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	const float deltaX = InputComponent->GetAxisValue(TEXT("Movement_X"));
	CharacterMovement->AddInputVector(FVector(0, 1, 0) * deltaX);

	const float deltaY = InputComponent->GetAxisValue(TEXT("MOVEMENT_Y"));
	CharacterMovement->AddInputVector(FVector(1, 0, 0) * deltaY);
}

// Called to bind functionality to input
void AMrCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMrCharacter::TestFunction()
{

}
