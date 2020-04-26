// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Walker.h"

// Sets default values for this component's properties
UWalker::UWalker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWalker::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();

	// FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	// FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	// FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// ...
	SetupInputComponent();
}


// Called every frame
void UWalker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWalker::MoveForward(float Val)
{
	if (Val != 0)
	{
		//UCharacterMovementComponent* MovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
		//MovementComponent->AddImpulse(GetOwner()->GetActorForwardVector() * PlayerWalkSpeed, false);
		//UE_LOG(LogTemp, Warning, TEXT("pos: %f"), GetOwner()->GetActorLocation().X);
		//UE_LOG(LogTemp, Warning, TEXT("pos: %f %f %f"), GetOwner()->GetActorForwardVector().X, GetOwner()->GetActorForwardVector().Y, GetOwner()->GetActorForwardVector().Z);
		FVector NewLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * PlayerWalkSpeed * GetWorld()->GetDeltaSeconds() * Val;
		FTransform ActorTransform = OwnerActor->GetActorTransform();
		ActorTransform.SetLocation(NewLocation);
		OwnerActor->SetActorTransform(ActorTransform);
	}
}

void UWalker::StrafeRight(float Val)
{
	if (Val != 0)
	{
		FVector NewLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorRightVector() * PlayerWalkSpeed * GetWorld()->GetDeltaSeconds() * Val;
		FTransform ActorTransform = OwnerActor->GetActorTransform();
		ActorTransform.SetLocation(NewLocation);
		OwnerActor->SetActorTransform(ActorTransform);
	}
}

void UWalker::LookRight(float Val)
{
	if (Val != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Right %f"), Val);
		FRotator NewRotation = OwnerActor->GetActorRotation() + FRotator(0, Val, 0);
		UE_LOG(LogTemp, Warning, TEXT("NewRotation: %f %f %f"), NewRotation.Pitch, NewRotation.Yaw, NewRotation.Roll);
		FQuat QuatRotation = FQuat(NewRotation);
		//OwnerActor->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		OwnerActor->SetActorRotation(NewRotation);
		
	}
}

void UWalker::LookUp(float Val)
{
	if (Val != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Up %f "), Val);
	}
}

void UWalker::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &UWalker::MoveForward);
		InputComponent->BindAxis("StrafeRight", this, &UWalker::StrafeRight);
		InputComponent->BindAxis("LookRight", this, &UWalker::LookRight);
		InputComponent->BindAxis("LookUp", this, &UWalker::LookUp);
		//InputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);
		//InputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No input component found!"));
	}
	
}

