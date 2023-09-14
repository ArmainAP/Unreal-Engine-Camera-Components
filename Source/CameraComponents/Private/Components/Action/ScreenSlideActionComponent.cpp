// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Components/Action/ScreenSlideActionComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UScreenSlideActionComponent::UScreenSlideActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called every frame
void UScreenSlideActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FVector2D CurrentMousePositionRatio = GetMousePositionRatio();

	FVector2D Delta = CurrentMousePositionRatio - ScreenSlidingOriginRatio;
	Delta.Normalize();
	Delta.X *= FMath::Min(FMath::Abs(Delta.X), ScreenSlidingMaxRatio) / ScreenSlidingMaxRatio;
	Delta.Y *= FMath::Min(FMath::Abs(Delta.Y), ScreenSlidingMaxRatio) / ScreenSlidingMaxRatio;
	
	OnUpdateSliding.Broadcast(Delta);
}

void UScreenSlideActionComponent::StartScreenSlide()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController)) return;

	ScreenSlidingOriginRatio = GetMousePositionRatio();
	SetComponentTickEnabled(true);
}

void UScreenSlideActionComponent::EndScreenSlide()
{
	SetComponentTickEnabled(false);
}

FVector2D UScreenSlideActionComponent::GetMousePositionRatio() const
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController)) return FVector2D::ZeroVector;
	
	FVector2D Origin = FVector2D::UnitVector;
	PlayerController->GetMousePosition(Origin.X, Origin.Y);

	FIntPoint Size = FIntPoint(1);
	PlayerController->GetViewportSize(Size.X, Size.Y);

	return Origin / Size;
}
