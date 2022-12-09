// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "BonusShield.generated.h"

UCLASS()
class MYARCADE_API ABonusShield : public ABonus
{
	GENERATED_BODY()
	
protected:

		virtual void BonusCollected_Implementation() override;
};