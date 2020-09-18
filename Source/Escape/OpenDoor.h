// Copyright Raphael Hamzagic de Carvalho 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	UPROPERTY(EditAnywhere)
	float DoorOpenYawOffset = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenAndCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	float DoorClosedYaw;
	float DoorTargetYaw;
	void TickDoor(float DeltaTime);
	float DoorLastOpenedTime = 0.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	float CountMassOnPressurePlate() const;

	UPROPERTY(EditAnywhere)
	float RequiredMassToOpen = 50.f;

	UAudioComponent* AudioComponent = nullptr;
	bool HasOpenDoorAudioPlayed = false;
	bool HasCloseDoorAudioPlayed = true;

	void FindAudioComponent();
};
