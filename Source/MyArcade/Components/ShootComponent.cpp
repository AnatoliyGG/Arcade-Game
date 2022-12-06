// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Engine/world.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
	:
	ShootDelay(1.f)
{

}

// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
}	

void UShootComponent::Shoot()
{
	for (FShootInfo ShootInfo : ShootInfos)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);

		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

		AShootProjectitle* Projectitle = GetWorld()->SpawnActor<AShootProjectitle>(ShootInfo.ProjectitleClass, SpawnLocation, SpawnRotation, SpawnParameters);
		if(Projectitle) Projectitle->Damage = ShootInfo.Damage;
	}
}

void UShootComponent::StartShooting()
{
	// 1-таймер, 2-где вызывается функция, 3-какая функция, 4-периодичность,, 5-цикличность таймера
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootDelay, true, ShootDelay);
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}
