// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "Components/ShootComponent.h"
#include "MyArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BLueprintType)
struct  FShootInfoLevel
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};

UCLASS()
class MYARCADE_API AMyArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyArcadeGameModeBase();

	virtual void BeginPlay() override;

protected:

	FTimerHandle RecoverTimer;
	FTimerHandle IncreaseDifficutlyTimer;

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	bool IsGameOver;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnController* EnemySpawnController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Healts")
	UGameHealthComponent* HealtsComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPoints(int Points);

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool ChangeShootLevel(bool Up);
	
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float IncreaseDifficutlyPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class AMainPlayer* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int GamePoints;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TArray<FShootInfoLevel> ShootInfoLevels;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
	int CurrentShootLevel;
};