// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent()
	:
	Healts(3)
{

}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No PlayerPawn"));
		return;
	}
}

void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healts += ByValue;

	HealtsChanged.Broadcast(ByValue);

	if (Healts <= 0) HealtsEnded.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Health changed: %i"), Healts);
}

int UGameHealthComponent::GetHealts()
{
	return Healts;
}
