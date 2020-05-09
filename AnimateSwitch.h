// Copyright Jacob Ward 2020

#pragma once

#include "GenericPlatform/GenericPlatformMath.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimateSwitch.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WANDERER_API UAnimateSwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimateSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AnimateForward(float DeltaTime);
	void AnimateBackward(float DeltaTime);
	void ActivateSwitchAnimation();
	bool GetActivation();
	
private:
	bool GetSwitchState();
	FVector GetCurrentRotation();
	FVector GetCurrentLocation();
	bool CheckRotation(FVector Target);
	bool CheckTranslation(FVector Target);
	UPROPERTY(EditAnywhere)
	bool bRotate = false;
	UPROPERTY(EditAnywhere)
	FVector RotationVector = {0,0,0};
	UPROPERTY(EditAnywhere)
	bool bTranslate = false;
	UPROPERTY(EditAnywhere)
	FVector TranslationVector = {0,0,0};
	UPROPERTY(EditAnywhere)
	bool bCanReverse = false;
	UPROPERTY(EditAnywhere)
	float SwitchSpeed = 1;
	UPROPERTY(EditAnywhere)
	float SwitchRotateSpeed = 1;

	bool bActivated = false;

	bool bInitialSwitchState = false;
	FVector InitialRotation = {0,0,0};
	FVector InitialPosition = {0,0,0};

	UPROPERTY(EditAnywhere)
	float RotationTolerance = 0.01;
	UPROPERTY(EditAnywhere)
	float TranslationTolerance = 0.01;
};
