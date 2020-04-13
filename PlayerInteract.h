// Copyright Jacob Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerInteract.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UPlayerInteract : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	bool bDebugLines = false;

	UPROPERTY(EditAnywhere)
	float PlayerReach = 100.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr; 

	void Grab();
	bool bObjectGrabbed = false;
	void Release();
	void Throw();
	UPROPERTY(EditAnywhere)
	float PlayerThrowForce = 500000.0f;
	void FindPhysicsHandle();
	void SetupInputComponent();
	void InteractWithObject();
	

	FHitResult GetFirstPhysicsBodyInReach() const;//return first actor within reach with a physics body
	FHitResult GetFirstInteractableInReach() const; //return first actor within reach that is an interactable, e.g. a switch.
	FVector GetReachEnd() const;//Returns vector of point at reach end
		
};
