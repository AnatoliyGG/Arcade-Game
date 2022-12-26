// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MyArcade/Components/ShootComponent.h"
#include "MainPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class MYARCADE_API AMainPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector TouchLocation);
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector TouchLocation);

	virtual void PossessedBy(AController* NewController) override;

	APlayerController* Player_Controller;

	FVector2D MoveLimit;

private:

	FVector2D TouchLocation;

	bool Touching;

	UMaterialInterface* PawnMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to inputvc
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
	bool CanBeDamaged();
	bool CanBeDamaged_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	//void RevieveAneDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* PawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	float TouchMoveSensivity;

	UPROPERTY(BlueprintAssignable, Category = "Healths")
	FPawnDamagedEvent PawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* DestroyParticle;
};
