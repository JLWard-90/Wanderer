// Copyright Jacob Ward 2020

#include "GameFramework/Actor.h"
#include "AnimateSwitch.h"
#include "DoorSwitch.h"

// Sets default values for this component's properties
UDoorSwitch::UDoorSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorSwitch::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (bAutomateSwitchOnTriggerVolume && bAutoSwitchOnCharacterEnterVolume)
	{
		//If we want to trigger switch with the player character entering the trigger volume
		AutoSwitchTriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}


// Called every frame
void UDoorSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	AutomateSwitchOnTrigger();
}

bool UDoorSwitch::GetSwitchState() const
{
	return bDoorSwitch;
}

void UDoorSwitch::SetSwitchState(bool bNewState)
{
	bDoorSwitch = bNewState;
}

void UDoorSwitch::FlipSwitchState()
{
	if(CheckIfSwitchAnimation())
	{
		UAnimateSwitch* AnimationComponent = GetOwner()->FindComponentByClass<UAnimateSwitch>();
		if (bDoorSwitch && !AnimationComponent->GetActivation())
		{
			bDoorSwitch = false;
			UE_LOG(LogTemp, Warning, TEXT("Activating animation"));
			AnimationComponent->ActivateSwitchAnimation();
			return;
		}
		if (!AnimationComponent->GetActivation()) 
		{
			bDoorSwitch = true;
			UE_LOG(LogTemp, Warning, TEXT("Activating animation"));
			AnimationComponent->ActivateSwitchAnimation();
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("No Animation component found"));
	if (bDoorSwitch)
	{
		bDoorSwitch = false;
	}
	else 
	{
		bDoorSwitch = true;
	}
}

bool UDoorSwitch::CheckIfSwitchAnimation()
{
	UAnimateSwitch* AnimationComponent = GetOwner()->FindComponentByClass<UAnimateSwitch>();
	if (AnimationComponent != nullptr)
	{
		return true;
	}
	return false;
}

void UDoorSwitch::AutomateSwitchOnTrigger()
{
	if (bAutomateSwitchOnTriggerVolume && AutomateSwitchTriggerVolume != nullptr && AutoSwitchTriggerActor != nullptr && !bSwitchAutoFlipped)
	{
		TArray<AActor*> OverlappingActors;
		AutomateSwitchTriggerVolume->GetOverlappingActors(OUT OverlappingActors);
		for (AActor* ActorPtr : OverlappingActors)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *ActorPtr->GetName(), *AutoSwitchTriggerActor->GetName());
			if (ActorPtr == AutoSwitchTriggerActor)
			{
				bSwitchAutoFlipped = true;
				FlipSwitchState();
			}
		}
	}
}

