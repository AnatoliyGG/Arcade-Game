// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectitle.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AShootProjectitle::AShootProjectitle()
	:
	ProjectitleSpeed(1000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectitleCollision"));
	RootComponent = Collision;
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AShootProjectitle::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
		Collision->IgnoreComponentWhenMoving(OwnerCollision, true);
		OwnerCollision->IgnoreComponentWhenMoving(Collision, true);

		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectitle::OnProjectitleOverlap);
}

void AShootProjectitle::OnProjectitleOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return; // if no overlapped actor or it is a pawn

	if (!GetOwner()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;
	AController* instigator = PawnOwner->GetController();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, instigator, this, UDamageType::StaticClass());

	Destroy();
}

// Called every frame
void AShootProjectitle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectitleSpeed * DeltaTime, 0.f, 0.f));
}

