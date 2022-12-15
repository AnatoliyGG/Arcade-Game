// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "BonusShootLevelUp.generated.h"

UCLASS()
class MYARCADE_API ABonusShootLevelUp : public ABonus
{
	GENERATED_BODY()
	
protected:

	virtual void BonusCollected_Implementation() override;


};