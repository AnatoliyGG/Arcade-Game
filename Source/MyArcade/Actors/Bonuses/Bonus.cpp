// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABonus::ABonus()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(50);
}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{

}