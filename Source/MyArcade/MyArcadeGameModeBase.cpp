// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyArcadeGameModeBase.h"
#include "Engine/world.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/MainPlayer.h"

AMyArcadeGameModeBase::AMyArcadeGameModeBase()
	:
	PlayerRecoverTime(3)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealtsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealtsComponent"));
}

void AMyArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HealtsComponent->HealtsEnded.AddDynamic(this, &AMyArcadeGameModeBase::EndGame);

	PlayerPawn = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerPawn->PawnDamaged.AddDynamic(this, &AMyArcadeGameModeBase::ExplodePawn);
}

void AMyArcadeGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealtsComponent->ChangeHealths(-1);

	if (!IsGameOver)
	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AMyArcadeGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void  AMyArcadeGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AMyArcadeGameModeBase::EndGame()
{
	IsGameOver = true;

	EnemySpawnController->SetActive(false);

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Log, TEXT("Game Over"));
}

void AMyArcadeGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}