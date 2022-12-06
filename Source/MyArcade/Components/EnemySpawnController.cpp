// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnController.h"
#include "Engine/world.h"
#include "TimerManager.h"

// Called when the game starts
void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();

	StartSpawnStage();
}

void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();
	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UEnemySpawnController::StartSpawnStage()
{ 
	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num()-1)];

	EnemiesSpawned = 0;

	SpawnEnemy();

	// 1-таймер, 2-где вызывается функция, 3-какая функция, 4-периодичность,, 5-цикличность таймера
	GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnController::StartSpawnStage, Random.RandRange(StageMinDelay, StageMaxDelay), false);
}

void UEnemySpawnController::SpawnEnemy() 
{
	FActorSpawnParameters PawnParameters;

	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, PawnParameters);

	EnemiesSpawned++;
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);
	}
}