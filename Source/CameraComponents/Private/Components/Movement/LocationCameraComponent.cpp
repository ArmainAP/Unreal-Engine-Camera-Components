// Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "Components/Movement/LocationCameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ULocationCameraComponent::Setup_Implementation(USceneComponent* InTargetComponent)
{
	Super::Setup_Implementation(InTargetComponent);
	SetDesiredLocation(TargetComponent->GetComponentLocation());
}

void ULocationCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bTerrainHeightAdaptation)
	{
		const float NewZ = GetTerrainHeightAdaptationValue();
		const FVector NewLocation = FVector(DesiredLocation.X, DesiredLocation.Y, NewZ);
		SetDesiredLocation(NewLocation);
	}

	if(bApplyLag)
	{
		const FVector TickDesiredLocation = FMath::VInterpTo(TargetComponent->GetComponentLocation(), DesiredLocation, DeltaTime, LagSpeed); 
		TargetComponent->SetWorldLocation(TickDesiredLocation);
	}
}

void ULocationCameraComponent::DebugTick(const float DeltaTime)
{
	Super::DebugTick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Location: %s"), *DesiredLocation.ToString()));

	if(bApplyLag)
	{
		DrawDebugSphere(GetWorld(), DesiredLocation, 5.f, 8, FColor::Yellow);
		DrawDebugDirectionalArrow(GetWorld(), TargetComponent->GetComponentLocation(), DesiredLocation, 10.0f, FColor::Yellow);
	}
}

void ULocationCameraComponent::Move(const FVector& Direction)
{
	MoveForward(Direction.X);
	MoveRight(Direction.Y);
	MoveUp(Direction.Z);
}

void ULocationCameraComponent::MoveForward(const float Value)
{
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(TargetComponent->GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
									? Value * ScaleMovementSpeed.GetClampedValue(MovementSpeed * GetMovementScale())
									: Value * MovementSpeed;
	SetDesiredLocation(DesiredLocation + ForwardVector * LastDeltaTime * MovementScale);
}

void ULocationCameraComponent::MoveRight(const float Value)
{
	const FVector RightVector = UKismetMathLibrary::GetRightVector(TargetComponent->GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
									? Value * ScaleMovementSpeed.GetClampedValue(MovementSpeed * GetMovementScale())
									: Value * MovementSpeed;
	SetDesiredLocation(DesiredLocation + RightVector * LastDeltaTime * MovementScale);
}

void ULocationCameraComponent::MoveUp(const float Value)
{
	const FVector UpVector = UKismetMathLibrary::GetUpVector(TargetComponent->GetComponentRotation());
	const float MovementScale = (ScaleMovementSpeed.bConstrainMinimum || ScaleMovementSpeed.bConstrainMaximum)
									? Value * ScaleMovementSpeed.GetClampedValue(MovementSpeed * GetMovementScale())
									: Value * MovementSpeed;
	SetDesiredLocation(DesiredLocation + UpVector * LastDeltaTime * MovementScale);
}

void ULocationCameraComponent::SetDesiredLocation(const FVector NewLocation)
{
	DesiredLocation = GetCorrectedDestinationFromRestrictions(NewLocation);
	if(!bApplyLag)
	{
		TargetComponent->SetWorldLocation(DesiredLocation);
	}
}

FVector ULocationCameraComponent::GetCorrectedDestinationFromRestrictions(FVector Destination) const
{
	Destination.X = ConstraintX.GetClampedValue(Destination.X);
	Destination.Y = ConstraintY.GetClampedValue(Destination.Y);
	Destination.Z = ConstraintZ.GetClampedValue(Destination.Z);
	return Destination;
}

float ULocationCameraComponent::GetMovementScale_Implementation()
{
	if (bTraceGround)
	{
		FHitResult HitResult;
		const FVector End = DesiredLocation - FVector::UpVector * TNumericLimits<float>::Max();
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), DesiredLocation, End, TraceGroundChannels, true, {},
		                                                bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		                                                HitResult, true);
		GroundLevel = HitResult.bBlockingHit ? HitResult.Distance : FMath::Abs(TargetComponent->GetComponentLocation().Z);
	}

	if(GroundLevel == 0.0f || ScalingDistanceReference == 0.0f)
	{
		return 1.0f;
	}
	
	return GroundLevel / ScalingDistanceReference;
}

float ULocationCameraComponent::GetTerrainHeightAdaptationValue_Implementation()
{
	FHitResult HitResult;
	const FVector End = DesiredLocation - FVector::UpVector * TNumericLimits<float>::Max();
	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), DesiredLocation, End, TraceGroundChannels, true, {},
													bDebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
													HitResult, true);

	
	if (HitResult.bBlockingHit)
	{
		//if (DesiredLocation.Z - HitResult.ImpactPoint.Z != KINDA_SMALL_NUMBER)
			return HitResult.ImpactPoint.Z + DesiredGroundDistance;
	}
	
	return DesiredLocation.Z;
}