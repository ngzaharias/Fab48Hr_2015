// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UWorld;

#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

UCLASS(Blueprintable)
class SWALLOWCOLAPSETHIEF_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};