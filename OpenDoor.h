// Copyright Jacob Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorSwitch.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime) const;
	void CloseDoor(float DeltaTime) const;
	float TotalMassOfActors() const;//Mass of actors on trigger
	void FindAudioComponent();
	bool CheckSwitchState();

private:
	float ClosedYaw;
	UPROPERTY(EditAnywhere)
	bool bStartClosed = true;
	UPROPERTY(EditAnywhere)
	float RelativeOpenYaw = 90;
	UPROPERTY(EditAnywhere)
	float DoorOpenCloseSpeed = 3.f;
	UPROPERTY(EditAnywhere)
	float RequiredMass = 40.f;

	UPROPERTY(EditAnywhere)
	bool bAutoCloseDoor = false;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;
	float DoorTimer = 0.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenDoorTrigger = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	bool bDoorOpen = false;

	//Parameters concerning opening a door with a switch:
	UPROPERTY(EditAnywhere)
	bool bOpenDoorWithSwitch = false;
	bool bDoorOpenedBySwitch = false;
	
	UPROPERTY(EditAnywhere)
	AActor* DoorSwitchObject;
};
