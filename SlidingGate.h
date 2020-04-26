// Copyright Jacob Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorSwitch.h"
#include "SlidingGate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API USlidingGate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingGate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenGate(float DeltaTime) const;
	void CloseGate(float DeltaTime) const;
	bool CheckSwitchState();

private:
	float ClosedHeight;
	UPROPERTY(EditAnywhere)
	bool bStartClosed = true;	
	UPROPERTY(EditAnywhere)
	float RelativeOpenHeight = 10;
};
