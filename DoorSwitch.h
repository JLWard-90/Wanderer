// Copyright Jacob Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorSwitch.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UDoorSwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool GetSwitchState() const;
	void SetSwitchState(bool bState);
	void FlipSwitchState();

private:
	UPROPERTY(EditAnywhere)
	bool bDoorSwitch = false;

};
