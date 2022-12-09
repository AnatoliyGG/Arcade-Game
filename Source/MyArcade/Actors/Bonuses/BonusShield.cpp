// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "MyArcade/Pawns/MainPlayer.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	AMainPlayer* PlayerPawn = Cast<AMainPlayer>(Pawn);
	if (!PlayerPawn) return;

	Super::BonusCollected_Implementation();
}