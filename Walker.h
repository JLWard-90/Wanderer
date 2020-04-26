// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Walker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UWalker : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:	
	// Sets default values for this component's properties
	UWalker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();
	void MoveForward(float Val);
	void StrafeRight(float Val);
	void LookRight(float Val);
	void LookUp(float Val);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	UInputComponent* InputComponent = nullptr; 

	UPROPERTY(EditAnywhere)
	float PlayerWalkSpeed = 600;
		
	AActor* OwnerActor;
};
