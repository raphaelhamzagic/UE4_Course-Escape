// Copyright Raphael Hamzagic de Carvalho 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Reach = 100.f;
	FVector StartReachLocation = FVector::ZeroVector;
	FVector EndReachLocation = FVector::ZeroVector;
	void FindReachLocation();

	UPROPERTY(EditAnywhere)
	bool DebugReachLine = false;
	void TickDebugLine();

	UInputComponent* InputComponent = nullptr;
	void SetupInputComponent();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;	
	void FindPhysicsHandleComponent();
	FHitResult GetFirstPhysicsBodyInReach();
	void Grab();
	void TickGrabbedComponent();
	void Drop();
};
