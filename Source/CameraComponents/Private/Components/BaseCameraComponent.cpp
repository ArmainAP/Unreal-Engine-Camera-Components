// Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "Components/BaseCameraComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBaseCameraComponent::UBaseCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UBaseCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!IsValid(TargetComponent))
	{
		Setup_Implementation(GetOwner()->GetRootComponent());
	}
}

void UBaseCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	LastDeltaTime = DeltaTime;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bDebug)
	{
		DebugTick(DeltaTime);
	}
}

void UBaseCameraComponent::Setup_Implementation(USceneComponent* InTargetComponent)
{
	TargetComponent = InTargetComponent;
}
