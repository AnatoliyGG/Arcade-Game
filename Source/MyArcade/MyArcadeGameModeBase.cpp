// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyArcadeGameModeBase.h"
#include "Engine/world.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/MainPlayer.h"

AMyArcadeGameModeBase::AMyArcadeGameModeBase()
	:
	PlayerRecoverTime(3),
	CurrentShootLevel(-1),
	IncreaseDifficutlyPeriod(4.f)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));

	HealtsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealtsComponent"));
}

void AMyArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HealtsComponent->HealtsEnded.AddDynamic(this, &AMyArcadeGameModeBase::EndGame);

	PlayerPawn = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AMyArcadeGameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficutlyTimer, this, &AMyArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficutlyPeriod, true);
}

void AMyArcadeGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealtsComponent->ChangeHealths(-1);

	ChangeShootLevel(false);

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

	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AMyArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95, 0.4);
	UE_LOG(LogTemp, Log, TEXT("Difficutly increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void AMyArcadeGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AMyArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (!PlayerPawn) return false;

	int NewLevel =  FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootDelay = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
}