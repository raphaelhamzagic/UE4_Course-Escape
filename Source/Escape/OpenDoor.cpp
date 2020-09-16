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
	TargetYaw += GetOwner()->GetActorRotation().Yaw;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* AOwnerPtr = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), AOwnerPtr->GetActorRotation().Yaw);

	/*
	float Yaw = FMath::FInterpConstantTo(
		AOwnerPtr->GetActorRotation().Yaw,
		TargetYaw,
		DeltaTime,
		45
	);
	*/
	float Yaw = FMath::FInterpTo(
		AOwnerPtr->GetActorRotation().Yaw,
		TargetYaw,
		DeltaTime,
		2
	);
	AOwnerPtr->SetActorRotation(FRotator(0.f, Yaw, 0.f));

	UE_LOG(LogTemp, Warning, TEXT("New Yaw: %f"), AOwnerPtr->GetActorRotation().Yaw);
}

