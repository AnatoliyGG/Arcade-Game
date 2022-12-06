// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "MyArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class MYARCADE_API AMyArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyArcadeGameModeBase();

	virtual void BeginPlay() override;

protected:

	FTimerHandle RecoverTimer;

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
	
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class AMainPlayer* PlayerPawn;
};