// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnShield.generated.h"

class AMainPlayer;

UCLASS()
class MYARCADE_API APawnShield : public AActor
{
	GENERATED_BODY()

protected:

	FTimerHandle ShieldTimer;

	class AMainPlayer* ShieldForPawn;
	
public:	
	// Sets default values for this actor's properties
	APawnShield();

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void ActivateShield(AMainPlayer* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void DeactivateShield();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	float ShieldTime;
};
