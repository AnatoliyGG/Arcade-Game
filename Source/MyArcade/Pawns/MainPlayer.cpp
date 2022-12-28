// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/world.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AMainPlayer::AMainPlayer()
	:
	TouchMoveSensivity(1.f),
	MoveLimit(FVector2D(800.f, 700.f))
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");
	PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMash"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
}

void AMainPlayer::PossessedBy(AController* NewController)
{
	Player_Controller = Cast<APlayerController>(NewController);
}

bool AMainPlayer::CanBeDamaged_Implementation()
{
	return true;
}

void AMainPlayer::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);

	if(DestroyParticle) 
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Deactivate();
	}
}

void AMainPlayer::RecoverPawn_Implementation()
{
	SetActorEnableCollision(true);

	ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	PawnMaterial = PawnMesh->GetMaterial(0);
}

float AMainPlayer::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!CanBeDamaged()) return 0.f;

	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);

	PawnDamaged.Broadcast();

	return Damage;
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindTouch(IE_Pressed, this, &AMainPlayer::OnTouchPress);
//	InputComponent->BindTouch(IE_Released, this, &AMainPlayer::OnTouchReleased);

	InputComponent->BindTouch(IE_Repeat, this, &AMainPlayer::OnTouchMove);
}

void AMainPlayer::OnTouchMove(ETouchIndex::Type FingerIndex, FVector TouchCoor)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - TouchCoor.X, TouchLocation.Y - TouchCoor.Y);

	TouchDeltaMove *= TouchMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X*-1.f, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(TouchCoor.X, TouchCoor.Y);
}

void AMainPlayer::OnTouchPress(ETouchIndex::Type FingerIndex, FVector TouchCoor)
{
	TouchLocation = FVector2D(TouchCoor.X, TouchCoor.Y);
}
