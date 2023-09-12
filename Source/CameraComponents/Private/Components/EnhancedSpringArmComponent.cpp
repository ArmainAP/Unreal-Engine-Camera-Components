// Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "Components/EnhancedSpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UEnhancedSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDesiredZoom(TargetArmLength);
	SetDesiredSocketOffset(SocketOffset);
	SetDesiredTargetOffset(TargetOffset);
}

void UEnhancedSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	LastDeltaTime = DeltaTime;

	if (bDoCollisionTest && TargetArmLength != 0.0f)
	{
		FVector OriginLoc = GetComponentLocation();
		FVector CameraLoc = OriginLoc - GetComponentRotation().Vector() * TargetArmLength;
	
		FHitResult HitResult;
		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(SpringArm), false, GetOwner());
		GetWorld()->SweepSingleByChannel(HitResult, OriginLoc, CameraLoc, FQuat::Identity, ProbeChannel, FCollisionShape::MakeSphere(ProbeSize), QueryParams);
	
		if (HitResult.bBlockingHit)
		{
			TargetArmLength = (HitResult.Location - OriginLoc).Length();
		}
	}

	if(bEnableCameraLag)
	{
		SocketOffset = FMath::VInterpTo(SocketOffset, DesiredSocketOffset, DeltaTime, CameraLagSpeed);
		TargetOffset = FMath::VInterpTo(TargetOffset, DesiredTargetOffset, DeltaTime, CameraLagSpeed);
		TargetArmLength = FMath::FInterpTo(TargetArmLength, DesiredZoom, DeltaTime, CameraLagSpeed);
	}

	if(bDrawDebugLagMarkers)
	{
		DebugTick(DeltaTime);
	}
}

void UEnhancedSpringArmComponent::DebugTick(const float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Zoom: %f"), DesiredZoom));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Socket offset: %s"), *DesiredSocketOffset.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Target offset: %s"), *DesiredTargetOffset.ToString()));

	const FVector ComponentLocation = GetComponentLocation();
	DrawDebugSphere(GetWorld(), ComponentLocation, 5.f, 8, FColor::Green);

	const FVector DesiredTargetOffsetWorldLocation = ComponentLocation + DesiredTargetOffset;
	if (!DesiredTargetOffset.IsZero())
	{
		DrawDebugSphere(GetWorld(), DesiredTargetOffsetWorldLocation, 5.f, 8, FColor::Orange);
		DrawDebugDirectionalArrow(GetWorld(), ComponentLocation, DesiredTargetOffsetWorldLocation, 7.5f, FColor::Orange);
	}
	if (!DesiredSocketOffset.IsZero())
	{
		const FVector DesiredSocketOffsetWorldLocation = DesiredTargetOffsetWorldLocation + FRotationMatrix(GetComponentRotation()).TransformVector(DesiredSocketOffset);
		DrawDebugSphere(GetWorld(), DesiredSocketOffsetWorldLocation, 5.f, 8, FColor::Red);
		DrawDebugDirectionalArrow(GetWorld(), DesiredTargetOffsetWorldLocation, DesiredSocketOffsetWorldLocation, 7.5f, FColor::Red);
	}
}

void UEnhancedSpringArmComponent::Move(const FVector& Direction)
{
	MoveForward(Direction.X);
	MoveRight(Direction.Y);
	MoveUp(Direction.Z);
}

void UEnhancedSpringArmComponent::MoveForward(const float Value, const bool bMoveSocketOffset)
{
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
								? Value * ScaleMovementSpeed.GetClampedValue(OffsetSpeed * GetMovementScale())
								: Value * OffsetSpeed;
	if (bMoveSocketOffset)
	{
		ForwardVector = GetComponentRotation().UnrotateVector(ForwardVector);
		SetDesiredSocketOffset(DesiredSocketOffset + ForwardVector * LastDeltaTime * MovementScale);
	}
	else
	{
		SetDesiredTargetOffset(DesiredTargetOffset + ForwardVector * LastDeltaTime * MovementScale);
	}
}

void UEnhancedSpringArmComponent::MoveRight(const float Value, const bool bMoveSocketOffset)
{
	FVector RightVector = UKismetMathLibrary::GetRightVector(GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
								? Value * ScaleMovementSpeed.GetClampedValue(OffsetSpeed * GetMovementScale())
								: Value * OffsetSpeed;
	if (bMoveSocketOffset)
	{
		RightVector = GetComponentRotation().UnrotateVector(RightVector);
		SetDesiredSocketOffset(DesiredSocketOffset + RightVector * LastDeltaTime * MovementScale);
	}
	else
	{
		SetDesiredTargetOffset(DesiredTargetOffset + RightVector * LastDeltaTime * MovementScale);
	}
}

void UEnhancedSpringArmComponent::MoveUp(const float Value, const bool bMoveSocketOffset)
{
	FVector UpVector = UKismetMathLibrary::GetUpVector(GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
								? Value * ScaleMovementSpeed.GetClampedValue(OffsetSpeed * GetMovementScale())
								: Value * OffsetSpeed;
	if (bMoveSocketOffset)
	{
		UpVector = GetComponentRotation().UnrotateVector(UpVector);
		SetDesiredSocketOffset(DesiredSocketOffset + UpVector * LastDeltaTime * MovementScale);
	}
	else
	{
		SetDesiredTargetOffset(DesiredTargetOffset + UpVector * LastDeltaTime * MovementScale);
	}
}

void UEnhancedSpringArmComponent::SetDesiredTargetOffset(FVector NewTargetOffset)
{
	DesiredTargetOffset = GetClampedOffset(NewTargetOffset);
	if(!bEnableCameraLag)
	{
		TargetOffset = DesiredTargetOffset;	
	}
}

void UEnhancedSpringArmComponent::SetDesiredSocketOffset(const FVector NewSocketOffset)
{
	DesiredSocketOffset = GetClampedOffset(NewSocketOffset);
	if(!bEnableCameraLag)
	{
		SocketOffset = DesiredSocketOffset;
	}
}

float UEnhancedSpringArmComponent::GetMovementScale_Implementation()
{
	return DesiredZoom / ScalingDistanceReference;
}

FVector UEnhancedSpringArmComponent::GetClampedOffset(FVector Offset) const
{
	Offset.X = ConstraintX.GetClampedValue(Offset.X);
	Offset.Y = ConstraintY.GetClampedValue(Offset.Y);
	Offset.Z = ConstraintZ.GetClampedValue(Offset.Z);
	return Offset;
}

void UEnhancedSpringArmComponent::ZoomIn(const float Value)
{
	SetDesiredZoom(DesiredZoom - GetZoomInValue(Value));
}

float UEnhancedSpringArmComponent::GetZoomInValue(const float Value)
{
	return (ScaleZoomSpeed.bConstrainMinimum || ScaleZoomSpeed.bConstrainMaximum) ? ScaleZoomSpeed.GetClampedValue(Value * ZoomSpeed * GetZoomInScale()) * LastDeltaTime :
							Value * ZoomSpeed * LastDeltaTime;
}

void UEnhancedSpringArmComponent::SetDesiredZoom(const float NewZoom)
{
	DesiredZoom = ConstraintZoom.GetClampedValue(NewZoom);
	if(!bEnableCameraLag)
	{
		TargetArmLength = DesiredZoom;
	}
}

float UEnhancedSpringArmComponent::GetZoomInScale_Implementation()
{
	return DesiredZoom / ScalingZoomReference;
}

float UEnhancedSpringArmComponent::GetZoomInValueAtDistance(const float Value, const float Distance) const
{
	return (ScaleZoomSpeed.bConstrainMinimum || ScaleZoomSpeed.bConstrainMaximum) ? ScaleZoomSpeed.GetClampedValue(Distance * Value * ZoomSpeed * Distance / ScalingZoomReference) * LastDeltaTime :
							Value * ZoomSpeed * LastDeltaTime;
}