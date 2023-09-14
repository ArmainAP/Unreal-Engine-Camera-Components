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

	const FVector CameraLocation = UGameplayStatics::GetPlayerCameraManager(InLocationCameraComponent, 0)->GetCameraLocation();
	FVector Direction = Location - CameraLocation;
	Direction.Normalize();
	InLocationCameraComponent->Move(Direction * Value);
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
