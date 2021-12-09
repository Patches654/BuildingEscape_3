// Houlihan

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"


// Does nothing, but helps us read the code, regarding out perameters...
#define OUT


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

	// Check for the physics handle componant.
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle is found.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle component"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		// IE is (I)nput(E)vent
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Grab Press"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Grabber Release Press"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get players viewpoint

	// This is an out perameter, we create to a variable, the GetPlayerViewPoint, modifies the variables. 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	
	// Creating the Vector, Converting the Rotation to a Vector and adding the two vectors together
	FVector LineTraceEnd = PlayerViewPointLocation + (GrabberLength * PlayerViewPointRotation.Vector());

	// Draw A debug line to check the resultant LineTraceEnd
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation,
		LineTraceEnd, 
		FColor::Green,
		false,
		0.f,
		0, 
		5.f
	);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace has hit: %s"), *HitActor->GetName());
	}
	
 
	// UE_LOG(LogTemp, Warning, TEXt("Actor that is hit %s "), AActor* InActor.ToString);

	// draw a line from player showing the reach
	// ray-cast out to the certain distance (reach)
	// see what it hits
}