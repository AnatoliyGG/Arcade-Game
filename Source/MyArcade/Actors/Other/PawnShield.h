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
	
public:	
	// Sets default values for this actor's properties
	APawnShield();

public:	

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void ActivateShield(AMainPlayer* PlayerPawn);
};
