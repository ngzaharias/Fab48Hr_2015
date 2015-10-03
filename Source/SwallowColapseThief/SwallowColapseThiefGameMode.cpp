// Fill out your copyright notice in the Description page of Project Settings.

#include "SwallowColapseThief.h"
#include "SwallowColapseThiefGameMode.h"

#include "MrCharacter.h"

ASwallowColapseThiefGameMode::ASwallowColapseThiefGameMode()
{

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
