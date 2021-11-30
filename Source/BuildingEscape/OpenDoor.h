// Houlihan

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
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
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	
private:

float DoorYawPosition;
float DoorLastOpenedTime = 0.f;
float TimeSinceLeftPressurePlate = 0.f;

UPROPERTY(EditAnywhere)
float DoorCloseDelayTime = .5f;

// UPROPERTY(EditAnywhere)
AActor* ActorThatOpens;

UPROPERTY(EditAnywhere)
ATriggerVolume* DoorTriggerVolume;

UPROPERTY(EditAnywhere)
float DoorOpenTargetAngle = -90.f;

UPROPERTY(EditAnywhere)
float DoorCloseTargetAngle = 90.f;

UPROPERTY(EditAnywhere)
float DoorOpenVelocity = 1.f;

UPROPERTY(EditAnywhere)
float DoorCloseVelocity = 1.f;

};
