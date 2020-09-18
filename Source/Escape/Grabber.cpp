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

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector out_PlayerViewLocation;
	FRotator out_PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_PlayerViewLocation, out_PlayerViewRotation);

	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation %s"), *out_PlayerViewLocation.ToString(), *out_PlayerViewRotation.ToString());
	

	FVector LineTraceEnd = out_PlayerViewLocation + (out_PlayerViewRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(),
		out_PlayerViewLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.0f
	);
}

