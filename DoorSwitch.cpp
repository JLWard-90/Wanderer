// Fill out your copyright notice in the Description page of Project Settings.


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
	
}


// Called every frame
void UDoorSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	if (bDoorSwitch)
	{
		bDoorSwitch = false;
	}
	else 
	{
		bDoorSwitch = true;
	}
}

