// Copyright Jacob Ward 2020

#include "GameFramework/Actor.h"
#include "DoorSwitch.h"
#include "AnimateSwitch.h"

// Sets default values for this component's properties
UAnimateSwitch::UAnimateSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAnimateSwitch::BeginPlay()
{
	Super::BeginPlay();

	// ...
	bInitialSwitchState = GetSwitchState();
	UE_LOG(LogTemp, Warning, TEXT("%b"), bInitialSwitchState);
	InitialRotation = GetCurrentRotation();
	InitialPosition = GetCurrentLocation();
	if (!bTranslate)
	{
		TranslationVector = InitialPosition;
	}
	if (!bRotate)
	{
		RotationVector = InitialRotation;
	}
}


// Called every frame
void UAnimateSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bActivated)
	{
		if (GetSwitchState() != bInitialSwitchState)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Animating forward"));
			AnimateForward(DeltaTime);
		}
		if (bCanReverse && (GetSwitchState() == bInitialSwitchState))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Animating backward"));
			AnimateBackward(DeltaTime);
		}
	}
}

FVector UAnimateSwitch::GetCurrentRotation()
{
	FRotator rotation = GetOwner()->GetActorRotation();
	return {rotation.Roll, rotation.Pitch, rotation.Yaw};
}


FVector UAnimateSwitch::GetCurrentLocation()
{
	return GetOwner()->GetActorLocation();
}

bool UAnimateSwitch::GetSwitchState()
{
	bool SwitchState = GetOwner()->FindComponentByClass<UDoorSwitch>()->GetSwitchState();
	return SwitchState;
}

void UAnimateSwitch::AnimateForward(float DeltaTime)
{
	if (bRotate)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation.Roll = FMath::FInterpTo(CurrentRotation.Roll, RotationVector.X, DeltaTime,SwitchSpeed);
		CurrentRotation.Pitch = FMath::FInterpTo(CurrentRotation.Pitch, RotationVector.Y, DeltaTime,SwitchSpeed);
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, RotationVector.Z, DeltaTime,SwitchSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
	if (bTranslate)
	{
		FVector CurrentPosition = GetOwner()->GetActorLocation();
		CurrentPosition.X = FMath::FInterpTo(CurrentPosition.X, TranslationVector.X, DeltaTime, SwitchSpeed);
		CurrentPosition.Y = FMath::FInterpTo(CurrentPosition.Y, TranslationVector.Y, DeltaTime, SwitchSpeed);
		CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, TranslationVector.Z, DeltaTime, SwitchSpeed);
		GetOwner()->SetActorLocation(CurrentPosition);
	}
	if (CheckRotation(RotationVector) && CheckTranslation(TranslationVector))
	{
		bActivated = false;
	}
}

void UAnimateSwitch::AnimateBackward(float DeltaTime)
{
	if (bRotate)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		CurrentRotation.Roll = FMath::FInterpTo(CurrentRotation.Roll, InitialRotation.X, DeltaTime,SwitchSpeed);
		CurrentRotation.Pitch = FMath::FInterpTo(CurrentRotation.Pitch, InitialRotation.Y, DeltaTime,SwitchSpeed);
		CurrentRotation.Yaw = FMath::FInterpTo(CurrentRotation.Yaw, InitialRotation.Z, DeltaTime,SwitchSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
	if (bTranslate)
	{
		FVector CurrentPosition = GetOwner()->GetActorLocation();
		CurrentPosition.X = FMath::FInterpTo(CurrentPosition.X, InitialPosition.X, DeltaTime, SwitchSpeed);
		CurrentPosition.Y = FMath::FInterpTo(CurrentPosition.Y, InitialPosition.Y, DeltaTime, SwitchSpeed);
		CurrentPosition.Z = FMath::FInterpTo(CurrentPosition.Z, InitialPosition.Z, DeltaTime, SwitchSpeed);
		GetOwner()->SetActorLocation(CurrentPosition);
	}
	if (CheckRotation(InitialRotation) && CheckTranslation(InitialPosition))
	{
		bActivated = false;
	}
}

bool UAnimateSwitch::CheckTranslation(FVector target)
{
	FVector Current = GetCurrentLocation();
	if (abs(target.X - Current.X) < TranslationTolerance && abs(target.Y - Current.Y) < TranslationTolerance && abs(target.Z - Current.Z) < TranslationTolerance)
	{
		return true;
	}
	return false;
}

bool UAnimateSwitch::CheckRotation(FVector target)
{
	FVector Current = GetCurrentRotation();
	if (abs(target.X - Current.X) < TranslationTolerance && abs(target.Y - Current.Y) < TranslationTolerance && abs(target.Z - Current.Z) < TranslationTolerance)
	{
		return true;
	}
	return false;
}

void UAnimateSwitch::ActivateSwitchAnimation()
{
	bActivated = true;
}

bool UAnimateSwitch::GetActivation()
{
	return bActivated;
}