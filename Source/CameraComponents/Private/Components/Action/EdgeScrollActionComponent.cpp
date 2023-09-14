// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Components/Action/EdgeScrollActionComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEdgeScrollActionComponent::UEdgeScrollActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UEdgeScrollActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector2D MousePosition;
	FIntPoint ViewportSize;
	if (!GetRelevantData(MousePosition, ViewportSize))
	{
		return;
	}

	const FVector2D Direction = CalculateEdgeScrolling(MousePosition, ViewportSize);
	
	if (!IsEdgeScrolling && !Direction.IsZero())
	{
		IsEdgeScrolling = true;
		OnBeginEdgeScrolling.Broadcast();
	}

	if (IsEdgeScrolling && Direction.IsZero())
	{
		IsEdgeScrolling = false;
		OnEndEdgeScrolling.Broadcast();
	}

	if (IsEdgeScrolling)
	{
		OnUpdateEdgeScrolling.Broadcast(Direction);
	}
}

bool UEdgeScrollActionComponent::GetRelevantData(FVector2D& MousePosition, FIntPoint& ViewportSize) const
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController) || !PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		return false;
	}

	PlayerController->GetViewportSize(ViewportSize.X, ViewportSize.Y);
	return true;
}

FVector2D UEdgeScrollActionComponent::CalculateEdgeScrolling(const FVector2D MousePosition, const FVector2D ViewportSize) const
{
	const FVector2D Sensitivities = ViewportSize * EdgeScrollingSensitivity;
	
	// Helper lambda to compute axis value (X or Y).
	auto ComputeAxisValue = [&](const float mousePos, const float viewportSize, const float sensitivity) -> float {
		if (mousePos < sensitivity)
		{
			return -1.f * (UseEdgeScrollingStrength ? 1.0f - mousePos / sensitivity : 1.0f);
		}

		if (mousePos > viewportSize - sensitivity)
		{
			return (UseEdgeScrollingStrength ? 1.0f - (viewportSize - mousePos) / sensitivity : 1.0f);
		}
		return 0.f; // No scrolling needed.
	};

	FVector2D Direction = FVector2D::ZeroVector;
	Direction.X = ComputeAxisValue(MousePosition.X, ViewportSize.X, Sensitivities.X);
	Direction.Y = ComputeAxisValue(MousePosition.Y, ViewportSize.Y, Sensitivities.Y);
	return Direction;
}