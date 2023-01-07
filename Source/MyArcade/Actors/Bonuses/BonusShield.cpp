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

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerPawn; 
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APawnShield* Shield = GetWorld()->SpawnActor<APawnShield>(ShieldClass, SpawnParams);

	if (Shield) Shield->ActivateShield(PlayerPawn);

	Super::BonusCollected_Implementation();
}