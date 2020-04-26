// Copyright Jacob Ward 2020


#include "SlidingGate.h"

// Sets default values for this component's properties
USlidingGate::USlidingGate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingGate::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USlidingGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

void USlidingGate::OpenGate(float DeltaTime) const
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenGate"));
	}
	
void USlidingGate::CloseGate(float DeltaTime) const
	{
		UE_LOG(LogTemp, Warning, TEXT("CloseGate"));
	}

bool USlidingGate::CheckSwitchState()
	{
		return true;
	}