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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->InputComponent;
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Drop);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if (HitResult.GetActor())
	{
		FindReachLocation();
		
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, EName::NAME_None, EndReachLocation);

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("%f: Hit actor %s"),
			GetWorld()->GetRealTimeSeconds(),
			*HitResult.GetActor()->GetName()
		);
	}	
}

void UGrabber::Drop()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	StartReachLocation = FVector::ZeroVector;
	EndReachLocation = FVector::ZeroVector;

	if (DebugReachLine)
	{
		TickDebugLine();
	}
	TickGrabbedComponent();
}

void UGrabber::TickDebugLine()
{
	FVector OutPlayerViewLocation;
	FRotator OutPlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OutPlayerViewLocation, OutPlayerViewRotation);

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
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FindReachLocation();

	FHitResult OutHitObject;
	GetWorld()->LineTraceSingleByObjectType(
		OutHitObject,
		StartReachLocation,
		EndReachLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	);

	return OutHitObject;
}

void UGrabber::TickGrabbedComponent()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		FindReachLocation();
		PhysicsHandle->SetTargetLocation(EndReachLocation);
	}
}

void UGrabber::FindReachLocation()
{
	if (StartReachLocation.IsZero() || EndReachLocation.IsZero())
	{
		FVector OutPlayerViewLocation;
		FRotator OutPlayerViewRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OutPlayerViewLocation, OutPlayerViewRotation);
		StartReachLocation = OutPlayerViewLocation;
		EndReachLocation = OutPlayerViewLocation + (OutPlayerViewRotation.Vector() * Reach);
	}
}
