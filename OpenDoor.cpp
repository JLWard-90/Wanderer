// Copyright Jacob Ward 2020
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	if (!OpenDoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenDoorTrigger undefined in {%s}:OpenDoor"), *(GetOwner()->GetName()));
	}
	if (bStartClosed) //Assume doors are either opened or closed.
	{
		ClosedYaw = GetOwner()->GetActorRotation().Yaw;
	}
	else
	{
		ClosedYaw = GetOwner()->GetActorRotation().Yaw - RelativeOpenYaw;
	}
	FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bOpenDoorWithSwitch) //Checks state of the switch if the door is opened by a switch
	{
		bDoorOpenedBySwitch = CheckSwitchState();
	}
	
	if ((bOpenDoorWithPressurePlate && TotalMassOfActors() >= RequiredMass) || (bOpenDoorWithSwitch && bDoorOpenedBySwitch))
	{
		OpenDoor(DeltaTime);
		if (!bDoorOpen && AudioComponent)
		{
			AudioComponent->Play();
			bDoorOpen = true;
		}
		DoorTimer = GetWorld()->GetTimeSeconds(); //Door Last Opened
	}
	else
	{
		if (bAutoCloseDoor && GetWorld()->GetTimeSeconds() >= DoorTimer+DoorCloseDelay)//If door open longer than x seconds
		{
			CloseDoor(DeltaTime);
			if (bDoorOpen && AudioComponent)
			{
				AudioComponent->Play();
				bDoorOpen = false;
			}
		}
	}

}


void UOpenDoor::OpenDoor(float DeltaTime) const
{
	FRotator CurrentDoorRotation = GetOwner()->GetActorRotation();
	CurrentDoorRotation.Yaw = FMath::FInterpTo(CurrentDoorRotation.Yaw, ClosedYaw+RelativeOpenYaw, DeltaTime,DoorOpenCloseSpeed);
	GetOwner()->SetActorRotation(CurrentDoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime) const
{
	FRotator CurrentDoorRotation = GetOwner()->GetActorRotation();
	CurrentDoorRotation.Yaw = FMath::FInterpTo(CurrentDoorRotation.Yaw, ClosedYaw, DeltaTime,DoorOpenCloseSpeed);
	GetOwner()->SetActorRotation(CurrentDoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float Total = 0.f;
	//Now iterate through all valid actors that overlap with trigger volume
	//find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if(!OpenDoorTrigger){return Total;}
	OpenDoorTrigger->GetOverlappingActors(OUT OverlappingActors);
	//add their masses
	for (AActor* ActorPtr : OverlappingActors)
	{
		Total += ActorPtr->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Total);
	return Total;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("{%s} missing audio component!"), *GetOwner()->GetName());
	}
}

bool UOpenDoor::CheckSwitchState()
{
	if (DoorSwitchObject == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("No Door switch assigned to {%s}"), *GetOwner()->GetName());
		return false;
	}
	return DoorSwitchObject->FindComponentByClass<UDoorSwitch>()->GetSwitchState();
}