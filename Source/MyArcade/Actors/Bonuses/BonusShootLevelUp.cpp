// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "MyArcade/MyArcadeGameModeBase.h"

void ABonusShootLevelUp::BonusCollected_Implementation()
{
	AMyArcadeGameModeBase* GameMode = Cast<AMyArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (!GameMode) return;

	GameMode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();
}