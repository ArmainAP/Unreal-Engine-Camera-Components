// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "CameraComponentsFunctionLibrary.h"

#include "Components/Movement/LocationCameraComponent.h"
#include "Components/Movement/RotationCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UCameraComponentsFunctionLibrary::RotateYawAroundPivot(URotationCameraComponent* InRotationCameraComponent,
                                                            ULocationCameraComponent* InLocationCameraComponent, const FVector Pivot, const float Value)
{
	if (!IsValid(InLocationCameraComponent) || !IsValid(InRotationCameraComponent))
	{
		return;
	}
	
	FVector Direction = InLocationCameraComponent->DesiredLocation - Pivot;
	const float OldYaw = InRotationCameraComponent->DesiredRotation.Yaw;
	InRotationCameraComponent->RotateYaw(Value);

	const float Delta = InRotationCameraComponent->DesiredRotation.Yaw - OldYaw;
	Direction = Direction.RotateAngleAxis(Delta, UKismetMathLibrary::GetUpVector(InRotationCameraComponent->DesiredRotation));
	InLocationCameraComponent->SetDesiredLocation(Pivot + Direction);
}

void UCameraComponentsFunctionLibrary::RotatePitchAroundPivot(URotationCameraComponent* InRotationCameraComponent,
	ULocationCameraComponent* InLocationCameraComponent, const FVector Pivot, const float Value)
{
	if (!IsValid(InLocationCameraComponent) || !IsValid(InRotationCameraComponent))
	{
		return;
	}
	
	FVector Direction = InLocationCameraComponent->DesiredLocation - Pivot;
	const float OldPitch = InRotationCameraComponent->DesiredRotation.Pitch;
	InRotationCameraComponent->RotatePitch(Value);
	
	const float Delta =  OldPitch - InRotationCameraComponent->DesiredRotation.Pitch;
	Direction = Direction.RotateAngleAxis(Delta, UKismetMathLibrary::GetRightVector(InRotationCameraComponent->DesiredRotation));
	InLocationCameraComponent->SetDesiredLocation(Pivot + Direction);
}

void UCameraComponentsFunctionLibrary::ZoomAtLocation(ULocationCameraComponent* InLocationCameraComponent, const float Value, const FVector Location)
{
	if (!IsValid(InLocationCameraComponent))
	{
		return;
	}

	// Get the camera manager
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(InLocationCameraComponent, 0);
	const FVector CameraLocation = CameraManager->GetCameraLocation();

	// Compute the world direction towards the target location
	FVector WorldDirection = Location - CameraLocation;
	WorldDirection.Normalize();

	// Convert the world direction to a direction in the local space of the TargetComponent
	const FVector LocalDirection = InLocationCameraComponent->InverseTransformVectorNoScale(WorldDirection);
	
	// Move the camera component
	InLocationCameraComponent->Move(LocalDirection * Value);
}


void UCameraComponentsFunctionLibrary::ZoomAtMousePosition(ULocationCameraComponent* InLocationCameraComponent, float Value,
	APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return;

	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	
	ZoomAtLocation(InLocationCameraComponent, Value, HitResult.ImpactPoint);
}

void UCameraComponentsFunctionLibrary::FocusOnActor(URotationCameraComponent* InRotationCameraComponent, ULocationCameraComponent* InLocationCameraComponent, const AActor* TargetActor,  const float DistanceMultiplier)
{
	if (!IsValid(InLocationCameraComponent) || !IsValid(InRotationCameraComponent) || !IsValid(TargetActor))
	{
		return;
	}

	// Calculate the bounding box of the actor.
	const FBox BoundingBox = TargetActor->GetComponentsBoundingBox();

	// Calculate the diagonal length of the bounding box.
	const float DiagonalLength = FVector::Dist(BoundingBox.Min, BoundingBox.Max);

	// Calculate the desired distance from the actor.
	const float DistanceFromTarget = DiagonalLength * DistanceMultiplier;

	const FVector Direction = (InLocationCameraComponent->DesiredLocation - TargetActor->GetActorLocation()).GetSafeNormal();
	const FVector NewCameraLocation = TargetActor->GetActorLocation() + Direction * DistanceFromTarget;
        
	InLocationCameraComponent->SetDesiredLocation(NewCameraLocation);
	InRotationCameraComponent->SetDesiredRotation((TargetActor->GetActorLocation() - NewCameraLocation).Rotation());
}
