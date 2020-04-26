// Copyright Jacob Ward 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WandererCharcter.generated.h"

UCLASS()
class WANDERER_API AWandererCharcter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWandererCharcter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();
	UCharacterMovementComponent* MovementComponent;
	void MoveForward(float Val);
	void StrafeRight(float Val);
	void LookRight(float Val);
	void LookUp(float Val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	float PlayerWalkSpeed = 600;

	AActor* OwnerActor;
};
