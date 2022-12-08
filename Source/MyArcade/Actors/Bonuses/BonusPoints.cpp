// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "MyArcade/MyArcadeGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	AMyArcadeGameModeBase* GameMode = Cast<AMyArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(Points);

	Super::BonusCollected_Implementation();
}