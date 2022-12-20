// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyArcade/Pawns/MainPlayer.h"

// Sets default values
ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(50);
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;
	if (!Cast<AMainPlayer>(OtherActor)) return;

	BonusCollected();
}

void ABonus::BonusCollected_Implementation()
{
	Destroy();
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WordlMoveOffset = -170.f * DeltaTime;
	AddActorLocalOffset(FVector(WordlMoveOffset, 0.f, 0.f));
}