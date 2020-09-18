// Copyright Raphael Hamzagic de Carvalho 2020


#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector OutPlayerViewLocation;
	FRotator OutPlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OutPlayerViewLocation, OutPlayerViewRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation %s"), *out_PlayerViewLocation.ToString(), *out_PlayerViewRotation.ToString());
	

	FVector LineTraceEnd = OutPlayerViewLocation + (OutPlayerViewRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(),
		OutPlayerViewLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.0f
	);


	FHitResult OutHitObject;

	bool IsHit = GetWorld()->LineTraceSingleByObjectType(
		OutHitObject,
		OutPlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	);

	if (IsHit) {
		
		UE_LOG(
			LogTemp, 
			Warning, 
			TEXT("%f: Hit actor %s"), 
			GetWorld()->GetRealTimeSeconds(),
			*OutHitObject.GetActor()->GetName()
		);
	}
}

