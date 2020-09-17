// Copyright Raphael Hamzagic de Carvalho 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorClosedYaw = GetOwner()->GetActorRotation().Yaw;

	if (!DoorTrigger) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component, but no DoorTrigger set."), *GetOwner()->GetName());
	}

	PlayerController = GetWorld()->GetFirstPlayerController();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerController) {		
		if (DoorTrigger && DoorTrigger->IsOverlappingActor(PlayerController->GetPawn()))
		{
			TargetYaw = DoorClosedYaw + DoorOpenYawOffset;
		}
		else
		{
			TargetYaw = DoorClosedYaw;
		}
		TickDoor(DeltaTime);
	}
}

void UOpenDoor::TickDoor(float DeltaTime)
{
	float Yaw = FMath::FInterpTo(
		GetOwner()->GetActorRotation().Yaw,
		TargetYaw,
		DeltaTime,
		2
	);
	GetOwner()->SetActorRotation(FRotator(0.f, Yaw, 0.f));
}