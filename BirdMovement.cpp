// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "BirdMovement.h"

// Sets default values for this component's properties
UBirdMovement::UBirdMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBirdMovement::BeginPlay()
{
	Super::BeginPlay();
	SelectNewTarget();
	// ...
	
}


// Called every frame
void UBirdMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (DistanceToTarget() <= TargetRadius)
	{
		SelectNewTarget();
	}
	MoveTowardsTarget(DeltaTime);
}

void UBirdMovement::SelectNewTarget()
{
	Target = FVector(FMath::RandRange(XboundLow,XboundHigh), FMath::RandRange(YboundLow,YboundHigh),FMath::RandRange(ZboundHigh,ZboundHigh));
}

void UBirdMovement::MoveTowardsTarget(float DeltaTime)
{
	FVector BirdPosition = GetOwner()->GetActorLocation();
	float NewXPosition = FMath::FInterpTo(BirdPosition.X, Target.X, DeltaTime, BirdSpeed);
	float NewYPosition = FMath::FInterpTo(BirdPosition.Y, Target.Y, DeltaTime, BirdSpeed);
	float NewZPosition = FMath::FInterpTo(BirdPosition.Z, Target.Z, DeltaTime, BirdSpeed);
	BirdPosition = {NewXPosition, NewYPosition, NewZPosition};
	GetOwner()->SetActorLocation(BirdPosition);
}

float UBirdMovement::DistanceToTarget() const
{
	FVector BirdPosition = GetOwner()->GetActorLocation();
	return FMath::Sqrt((BirdPosition.X-Target.X)*(BirdPosition.X-Target.X) + (BirdPosition.Y-Target.Y)*(BirdPosition.Y-Target.Y) + (BirdPosition.Z-Target.Z)*(BirdPosition.Z-Target.Z));
}

