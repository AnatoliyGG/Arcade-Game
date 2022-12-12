// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnShield.h"
#include "MyArcade/Pawns/MainPlayer.h"
#include "Engine/world.h"
#include "TimerManager.h"

// Sets default values
APawnShield::APawnShield()
	:	
	ShieldTime(5.f)
{

}

void APawnShield::ActivateShield(AMainPlayer* PlayerPawn)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}

	ShieldForPawn = PlayerPawn;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::KeepWorld,
		false
	);

	AttachToActor(PlayerPawn, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield::DeactivateShield, ShieldTime, false);
}

void APawnShield::DeactivateShield()
{
	if (!ShieldForPawn) return;

	ShieldForPawn;

	Destroy();
}

