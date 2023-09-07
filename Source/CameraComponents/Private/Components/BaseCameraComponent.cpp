//Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "Components/BaseCameraComponent.h"

// Sets default values for this component's properties
UBaseCameraComponent::UBaseCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseCameraComponent::Setup_Implementation(USpringArmComponent* InSpringArmComponent, UCameraComponent* InCameraComponent)
{
	SpringArmComponent = InSpringArmComponent;
	CameraComponent = InCameraComponent;
}