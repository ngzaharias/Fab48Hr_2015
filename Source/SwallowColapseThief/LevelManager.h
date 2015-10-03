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

	//UFUNCTION(BlueprintCallable, Category = "LevelManager")
	//	void JordanTestFunc(){}
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
		FVector2D GetLevelCenter();
	
	UFUNCTION(BlueprintCallable, Category = "LevelManager")
		float GetDistanceFromCenter(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "LevelManager")
		void DestroyRandomChunk();

	UFUNCTION(BlueprintCallable, Category = "LevelManager")
		void TrackLevelPiece(AActor* actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelManager")
		int32 width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelManager")
		int32 height;
private:
	//typedef TMap<float, AActor*> ActorMap;
	typedef TArray<AActor*> ActorArray;
	ActorArray levelChunks;
};