//Copyright to Kat Code Labs, SRL. All Rights Reserved.


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

	Owner = GetOwner();
}

void UBaseCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	LastTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if WITH_EDITORONLY_DATA
	if(bDebug)
	{
		DebugTick(DeltaTime);
	}
#endif
}
