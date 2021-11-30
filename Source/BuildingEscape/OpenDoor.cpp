// Houlihan

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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

	// Gets the inititial Door Yaw and sets the Target Yaw
	DoorYawPosition = GetOwner()->GetActorRotation().Yaw; 
	// CloseTargetYaw = DoorYawPosition;
	DoorOpenTargetAngle += DoorYawPosition;  // TargetYaw = TargetYaw + DoorYawPosition...

	// If we've implemented the the C++ OpenDoor File to an AActor but havent selected the pressure plate within its details...
	if(!DoorTriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Has OpenDoor C++ Class, But No Pressure Plate"), *GetOwner()->GetName());
	}
	// Gets the Player Pawn and sets it in ActorThatOpens, We use this to detect if the PlayerPawn is over the pressureplate...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (DoorTriggerVolume && DoorTriggerVolume->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);

		// Gets the time in seconds since the start of play...
		DoorLastOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpenedTime > DoorCloseDelayTime)
		{
			CloseDoor(DeltaTime);
		}		
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// Opens the door
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = FMath::FInterpTo(DoorRotation.Yaw, DoorOpenTargetAngle, DeltaTime, DoorOpenVelocity);
	GetOwner()->SetActorRotation(DoorRotation);
	// UE_LOG(LogTemp, Warning, TEXT("%f DoorRotation, %f Target"), DoorRotation.Yaw, DoorOpenTargetAngle);

}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// Closes the door
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = FMath::FInterpTo(DoorRotation.Yaw, DoorCloseTargetAngle, DeltaTime, DoorCloseVelocity);
	GetOwner()->SetActorRotation(DoorRotation);
	// UE_LOG(LogTemp, Warning, TEXT("%f DoorRotation, %f Target"), DoorRotation.Yaw, DoorCloseTargetAngle);
}

/*
I would use a component

I would know what to grab by only being able to grab the item that works
I would know what to grab by the way an item looks or is labeled
I would know what to grab by the way an item is shaped or its colour

My Item May pissibly be a Physics enamble ball

*/