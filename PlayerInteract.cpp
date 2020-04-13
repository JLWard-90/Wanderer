// Copyright Jacob Ward 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "DoorSwitch.h"
#include "PlayerInteract.h"

// Sets default values for this component's properties
UPlayerInteract::UPlayerInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInteract::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
	// ...
	
}


// Called every frame
void UPlayerInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bDebugLines)
	{
		FVector PlayerViewPointLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FVector LineTraceEnd = GetReachEnd();
		DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd,FColor(255,0,0),false,0.f,0,5.f);//Draw a debug line
	}
	
	// ...

	if(!PhysicsHandle){return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachEnd());
	}
}

void UPlayerInteract::Grab()
{
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	if(Hit.IsValidBlockingHit())
	{
		if (!PhysicsHandle){return;}
		UPrimitiveComponent* componentToGrab = Hit.GetComponent();
		PhysicsHandle->GrabComponentAtLocation
		(
			componentToGrab,
			NAME_None,
			GetReachEnd()
		);
		bObjectGrabbed = true;
	}
}

void UPlayerInteract::Throw()
{
	if (bObjectGrabbed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Throw object"));
		//UE_LOG(LogTemp, Error, TEXT("Throwing objects not yet implemented! using UPlayerInteract::Release()"));
		UPrimitiveComponent* GrabbedActor = PhysicsHandle->GetGrabbedComponent();
		UE_LOG(LogTemp, Warning, TEXT("Object: {%s}"), *GrabbedActor->GetOwner()->GetName());
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
		FVector ThrowVector = PlayerViewPointRotation.Vector() * PlayerThrowForce;
		GrabbedActor->AddForce(ThrowVector);
		Release();
	}
}

void UPlayerInteract::Release()
{
	if (!PhysicsHandle){return;}
	PhysicsHandle->ReleaseComponent();
	bObjectGrabbed = false;
}

FHitResult UPlayerInteract::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	// DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd,FColor(255,0,0),false,0.f,0,5.f);//Draw a debug line
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());//Raycast from player to a reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}


FVector UPlayerInteract::GetReachEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PlayerReach;
	return LineTraceEnd;
}

void UPlayerInteract::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); //Returns first component found of that class
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber::BeginPlay - No Physics handle found on {%s}"), *GetOwner()->GetName());
	}
}

void UPlayerInteract::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UPlayerInteract::Grab);
		InputComponent->BindAction("Release", IE_Released, this, &UPlayerInteract::Release);
		InputComponent->BindAction("Interact", IE_Pressed, this, &UPlayerInteract::InteractWithObject);
		InputComponent->BindAction("Throw", IE_Pressed, this, &UPlayerInteract::Throw);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber::BeginPlay - No Input Component found on {%s}"), *GetOwner()->GetName());
	}
}

void UPlayerInteract::InteractWithObject()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction not yet implemented!"));
	FHitResult InteractableHit = GetFirstInteractableInReach();
	if(InteractableHit.GetActor() == nullptr)
	{
		return;
	}
	if(InteractableHit.GetActor()->FindComponentByClass<UDoorSwitch>() != nullptr)
	{
		InteractableHit.GetActor()->FindComponentByClass<UDoorSwitch>()->FlipSwitchState();
		UE_LOG(LogTemp, Warning, TEXT("{%s} flipped"), *(InteractableHit.GetActor()->GetName()));
	}
}

FHitResult UPlayerInteract::GetFirstInteractableInReach() const
{
	FVector PlayerViewPointLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	// DrawDebugLine(GetWorld(),PlayerViewPointLocation,LineTraceEnd,FColor(255,0,0),false,0.f,0,5.f);//Draw a debug line
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());//Raycast from player to a reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		GetReachEnd(),
		FCollisionObjectQueryParams(),
		TraceParams
	);
	if (Hit.GetActor() == nullptr)
	{
		return Hit;
	}
	UDoorSwitch* doorSwitchClass = Hit.GetActor()->FindComponentByClass<UDoorSwitch>();
	if (doorSwitchClass != nullptr)
	{
		return Hit;
	}
	//Add any other additional classes to test for here.
	FHitResult DummyHit;
	return DummyHit;
}

