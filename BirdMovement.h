// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BirdMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UBirdMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBirdMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float XboundLow;
	UPROPERTY(EditAnywhere)
	float XboundHigh;
	UPROPERTY(EditAnywhere)
	float YboundLow;
	UPROPERTY(EditAnywhere)
	float YboundHigh;
	UPROPERTY(EditAnywhere)
	float ZboundLow;
	UPROPERTY(EditAnywhere)
	float ZboundHigh;
	UPROPERTY(EditAnywhere)
	float BirdSpeed=1;
	UPROPERTY(EditAnywhere)
	float TargetRadius = 2;

	void SelectNewTarget();
	void MoveTowardsTarget(float DeltaTime);
	float DistanceToTarget() const;
	FVector Target;
		
};
