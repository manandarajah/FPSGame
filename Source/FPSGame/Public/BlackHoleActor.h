// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHoleActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	/* Inner sphere destroys the overlapping components */
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* InnerSphereComponent;

	/* Outer sphere pulls components (that are physically simulating) towards the centre of the actor */
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* OuterSphereComponent;

	// Marked with ufunction to bind to overlap event
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};