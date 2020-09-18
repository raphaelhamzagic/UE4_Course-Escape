// Copyright Raphael Hamzagic de Carvalho 2020


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorClosedYaw = GetOwner()->GetActorRotation().Yaw;
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component, but no DoorTrigger set."), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && CountMassOnPressurePlate() >= RequiredMassToOpen)
	{
		DoorTargetYaw = DoorClosedYaw + DoorOpenYawOffset;
		DoorLastOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenedTime > DoorCloseDelay)
		{
			DoorTargetYaw = DoorClosedYaw;
		}
	}
	TickDoor(DeltaTime);

}

void UOpenDoor::TickDoor(float DeltaTime)
{
	float currentTime = GetWorld()->GetRealTimeSeconds();
	float Yaw = FMath::FInterpTo(
		GetOwner()->GetActorRotation().Yaw,
		DoorTargetYaw,
		DeltaTime,
		DoorOpenAndCloseSpeed
	);
	GetOwner()->SetActorRotation(FRotator(0.f, Yaw, 0.f));
}

float UOpenDoor::CountMassOnPressurePlate() const
{
	float TotalMass = 0.f;

	if (PressurePlate)
	{
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OverlappingActors);
		for (AActor*& OverlappingActor : OverlappingActors)
		{
			float ActorMass = OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			// UE_LOG(LogTemp, Warning, TEXT("Actor %s has %f kg of mass."), *OverlappingActor->GetName(), ActorMass);
			TotalMass += ActorMass;
		}
		// UE_LOG(LogTemp, Warning, TEXT("Total Mass is %f"), TotalMass);
	}

	return TotalMass;
}