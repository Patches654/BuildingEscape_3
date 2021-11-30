// Fill out your copyright notice in the Description page of Project Settings.

// Remember this is a C++ Class created from inside unreal engine...

#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	// Whatever AActor this class is attached to, it will return the name of the AActor and its transform (location)...
	// Use "Add Component" to add it to an AActor in Unreal... 
	FString ObjName = GetOwner()->GetName();
	FString ObjPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s at %s"), *ObjName, *ObjPosition)

}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

