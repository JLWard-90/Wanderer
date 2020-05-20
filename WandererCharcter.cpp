// Copyright Jacob Ward 2020


#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/Actor.h"
#include "WandererCharcter.h"

// Sets default values
AWandererCharcter::AWandererCharcter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(20.f, 90.0f);

}

// Called when the game starts or when spawned
void AWandererCharcter::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
	SetupInputComponent();
	MovementComponent = GetCharacterMovement();
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find movement component"));
	}
	CurrentPlayerSpeed = PlayerWalkSpeed;
}

// Called every frame
void AWandererCharcter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWandererCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWandererCharcter::SetupInputComponent()
{
	InputComponent->BindAxis("MoveForward", this, &AWandererCharcter::MoveForward);
	InputComponent->BindAxis("StrafeRight", this, &AWandererCharcter::StrafeRight);
	InputComponent->BindAxis("LookRight", this, &AWandererCharcter::LookRight);
	InputComponent->BindAxis("LookUp", this, &AWandererCharcter::LookUp);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Sprint",IE_Pressed, this, &AWandererCharcter::Sprint);
	InputComponent->BindAction("Sprint",IE_Released, this, &AWandererCharcter::StopSprinting);
}

void AWandererCharcter::MoveForward(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorForwardVector(), Val*CurrentPlayerSpeed);
	}
}

void AWandererCharcter::StrafeRight(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorRightVector(), Val*CurrentPlayerSpeed);
	}
}

void AWandererCharcter::LookRight(float Val)
{
	if (Val != 0)
	{
		AddControllerYawInput(Val);
	}
}

void AWandererCharcter::LookUp(float Val)
{
	if (Val != 0)
	{
		AddControllerPitchInput(Val);
	}
}

void AWandererCharcter::Sprint()
{
	CurrentPlayerSpeed = PlayerSprintSpeed;
	MovementComponent->MaxWalkSpeed = PlayerSprintSpeed;
}

void AWandererCharcter::StopSprinting()
{
	CurrentPlayerSpeed = PlayerWalkSpeed;
	MovementComponent->MaxWalkSpeed = PlayerWalkSpeed;
}