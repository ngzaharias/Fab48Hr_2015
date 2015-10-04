// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "SwallowColapseThiefGameMode.h"

#include "MrCharacter.h"

ASwallowColapseThiefGameMode::ASwallowColapseThiefGameMode()
{
	m_colours.Add(FColor(255, 0, 0));
	m_colours.Add(FColor(0, 255, 0));
	m_colours.Add(FColor(0, 0, 255));
	m_colours.Add(FColor(255, 0, 255));
}

void ASwallowColapseThiefGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < m_players; ++i)
	{
		UGameplayStatics::CreatePlayer(this->GetWorld(), i);
	}
}

void ASwallowColapseThiefGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FColor ASwallowColapseThiefGameMode::GetPlayerColour()
{
	FColor result = FColor(255, 255, 255);

	if (m_colours.Num() > 0)
	{
		result = m_colours[0];
		m_colours.RemoveAt(0);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, result, "PlayerColour");
	return result;
}

void ASwallowColapseThiefGameMode::StartGame()
{

}