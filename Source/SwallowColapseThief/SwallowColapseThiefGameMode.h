// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SwallowColapseThiefGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SWALLOWCOLAPSETHIEF_API ASwallowColapseThiefGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ASwallowColapseThiefGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category = "Multiplayer")
		int8 m_players;
};
