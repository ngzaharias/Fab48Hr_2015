// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MrCharacter.generated.h"

UCLASS(Blueprintable)
class SWALLOWCOLAPSETHIEF_API AMrCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMrCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void ActionBasic();
	virtual void ActionSpecial();

	virtual void Movement_X(float value);
	virtual void Movement_Y(float value);
	virtual void Direction_X(float value);
	virtual void Direction_Y(float value);

	FRotator CalculateRotation(float deltaX, float deltaY);


protected:
	
	void ChargeStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
		void ChargeTick();
	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void ChargeFinish();

public:

protected:
	FTimerDelegate ChargeFinishedCallback;

public:
	UPROPERTY(EditAnywhere, Category = "Abilities")
		float m_chargeForce;
	UPROPERTY(EditAnywhere, Category = "Abilities")
		float m_chargeTime;
	UPROPERTY(EditAnywhere, Category = "Abilities")
		float m_chargeCooldown;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
		bool m_isCharging;

	FTimerHandle m_chargeTimeHandle;
	FTimerHandle m_chargeCooldownHandle;
};
