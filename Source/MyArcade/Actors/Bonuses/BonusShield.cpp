// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "MyArcade/Pawns/MainPlayer.h"
#include "Engine/world.h"
#include "MyArcade/Actors/Other/PawnShield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	AMainPlayer* PlayerPawn = Cast<AMainPlayer>(Pawn);
	if (!PlayerPawn) return;

	APawnShield* Shield = GetWorld()->SpawnActor<APawnShield>(ShieldClass);

	Shield->ActivateShield(PlayerPawn);

	Super::BonusCollected_Implementation();
}