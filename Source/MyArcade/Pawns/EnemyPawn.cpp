// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "MyArcade/MyArcadeGameModeBase.h"
#include "Engine/world.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMash"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	HealthCompoonent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthCompoonent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);
	
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::KillPawn()   
{
	AMyArcadeGameModeBase* GameMode = Cast<AMyArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(DestroyPoints);

	SpawnBonuses();

	DestroyPawn();
} 

void AEnemyPawn::DestroyPawn()
{
	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	if (AppliedDamage > 0.f) DestroyPawn();
}  

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	

	for (FBonusChance Bonus : PossibleBonuses)
	{
		float RandChance = Random.RandRange(0.f, 100.f);
		if (RandChance < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WordlMoveOffset = -400.f * DeltaTime;
	AddActorLocalOffset(FVector(WordlMoveOffset, 0.f, 0.f));
}