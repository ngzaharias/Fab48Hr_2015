// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "LevelManager.h"
#include "LevelSegment.h"

#define BOX_SIZE 100.0f // Screw it. Until I figure out how to get levelSegments to report their size in LevelManager, I'm hardcoding it. 
static FVector originOffset(-650.f, -650.f, 0.f);

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

FVector2D ALevelManager::GetLevelCenter()
{
	float x = width * BOX_SIZE;
	float y = height * BOX_SIZE;
	return FVector2D(x/2, y/2);
}

float ALevelManager::GetDistanceFromCenter(AActor* actor)
{
	// DIDN'T INSTANTLY WORK. NOT IMPORTANT ENOUGH TO CARE


	//FVector pos;// = actor->GetActorLocation();
	//TArray<UStaticMeshComponent*> comps;
	//
	////hitActor->GetComponents(comps);
	//for (auto StaticMeshComponent : comps)
	//{
	//	pos = StaticMeshComponent->GetComponentLocation();
	//}
	//
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "ALevelManager::GetDistanceFromCenter");
	//if (actor)
	//{
	//	return 1.0f;
	//}

	return 0.0f;
}

void ALevelManager::DestroyRandomChunk()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "ALevelManager::DestroyRandomChunk");
	int32 size = activeChunks.Num();
	if (size == 0)
		return;

	int32 idx = FMath::RandRange(0, FMath::Min(size - 1, 5));
	int32 lvlIdx = activeChunks[idx];
	ExplodePiece(levelChunks[lvlIdx]);
	activeChunks.Remove(lvlIdx);
	
}

void ALevelManager::TrackLevelPiece(AActor* actor)
{
	levelChunks.Add(actor);// [GetDistanceFromCenter(actor)] = actor;
	activeChunks.Add(levelChunks.Num() - 1);
}

void ALevelManager::SortLevelChunks()
{
	while (activeChunks.Num() > 0)
	{
		int32 idx = GetfurtherestIdx();
		sortedActiveChunks.Add(idx);
		activeChunks.Remove(idx);
	}

	while (sortedActiveChunks.Num() > 0)
	{
		int32 idx = sortedActiveChunks[0];
		activeChunks.Add(idx);
		sortedActiveChunks.Remove(idx);
	}
}

int32 ALevelManager::GetfurtherestIdx()
{
	float biggestDist = 0.0f;
	int32 retVal = 0;
	for (int32 i = 0, size = activeChunks.Num(); i < size; ++i)
	{
		int32 idx = activeChunks[i];
		AActor* act = levelChunks[idx];
		FVector pos = act->GetActorLocation();
		float len = pos.SizeSquared();

		if (len > biggestDist)
		{
			biggestDist = len;
			retVal = idx;
		}
	}

	return retVal;
}