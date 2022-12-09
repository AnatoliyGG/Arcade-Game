// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnShield.h"
#include "MyArcade/Pawns/MainPlayer.h"

// Sets default values
APawnShield::APawnShield()
{

}

void APawnShield::ActivateShield(AMainPlayer* PlayerPawn)
{
	false;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::KeepWorld,
		false
	);

	AttachToActor(PlayerPawn, AttachRules);
}

void APawnShield::DeactivateShield()
{

}

