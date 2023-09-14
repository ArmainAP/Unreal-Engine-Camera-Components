// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Action/PreciseDragActionComponent.h"

#include "Components/Movement/LocationCameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPreciseDragActionComponent::UPreciseDragActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}

// Called every frame
void UPreciseDragActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(DraggedLocationCameraComponent))
	{
		return;
	}
	
	DraggedLocationCameraComponent->SetDesiredLocation(CalculateNewLocation());
}

void UPreciseDragActionComponent::StartDrag(ULocationCameraComponent* InLocationCameraComponent)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController)) return;
		
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(PreciseMouseDragCollisionChannel, PreciseMouseDragTraceComplex, HitResult);
	PreciseMouseDragOrigin = HitResult.ImpactPoint;
	DraggedLocationCameraComponent = InLocationCameraComponent;
	SetComponentTickEnabled(HitResult.IsValidBlockingHit());
}

void UPreciseDragActionComponent::StopDrag()
{
	SetComponentTickEnabled(false);
	DraggedLocationCameraComponent = nullptr;
	PreciseMouseDragOrigin = FVector::ZeroVector;
}


FVector UPreciseDragActionComponent::CalculateNewLocation() const
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController))
	{
		return FVector::ZeroVector;
	}
	
	FVector WorldPosition, Direction;
	PlayerController->DeprojectMousePositionToWorld(WorldPosition, Direction);

	// Calculate the intersection of the mouse ray with the drag plane, offset by camera's desired location
	const FVector MouseRayOffsetPoint = WorldPosition + (DraggedLocationCameraComponent->DesiredLocation - DraggedLocationCameraComponent->GetTargetComponentLocation());

	FVector MouseRayDragIntersection;
	MouseRayDragIntersection.Z = PreciseMouseDragOrigin.Z;
	MouseRayDragIntersection.X = MouseRayOffsetPoint.X + (PreciseMouseDragOrigin.Z - MouseRayOffsetPoint.Z) * Direction.X / Direction.Z;
	MouseRayDragIntersection.Y = MouseRayOffsetPoint.Y + (PreciseMouseDragOrigin.Z - MouseRayOffsetPoint.Z) * Direction.Y / Direction.Z;

	// Calculate the new position offset by the mouse drag
	return DraggedLocationCameraComponent->DesiredLocation - (MouseRayDragIntersection - PreciseMouseDragOrigin);
}
