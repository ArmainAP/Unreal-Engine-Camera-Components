// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Components/Movement/RotationCameraComponent.h"

void URotationCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bApplyLag)
	{
		const FQuat TickDesiredRotation = FMath::QInterpTo(TargetComponent->GetComponentQuat(), GetDesiredRotationWithOffset(), DeltaTime, LagSpeed);
		TargetComponent->SetWorldRotation(TickDesiredRotation);
	}
}

void URotationCameraComponent::Setup_Implementation(USceneComponent* InTargetComponent)
{
	Super::Setup_Implementation(InTargetComponent);

	SetDesiredRotation(TargetComponent->GetComponentRotation());
}

void URotationCameraComponent::RotatePitch(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewPitchOffset = DesiredRotationOffset.Pitch - LastDeltaTime * Value * RotationSpeed;
		SetDesiredPitchOffset(NewPitchOffset);
	}
	else
	{
		const float NewPitch = DesiredRotation.Pitch - LastDeltaTime * Value * RotationSpeed;
		SetDesiredPitch(NewPitch);
	}
}

void URotationCameraComponent::SetDesiredPitch(const float NewPitch)
{
	SetDesiredPitchValue(NewPitch);
	if(!bApplyLag)
	{
		TargetComponent->SetWorldRotation(GetDesiredRotationWithOffset());
	}
}

void URotationCameraComponent::RotateYaw(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewYawOffset = DesiredRotationOffset.Yaw - LastDeltaTime * Value * RotationSpeed;
		SetDesiredYawOffset(NewYawOffset);
	}
	else
	{
		const float NewYaw = DesiredRotation.Yaw - LastDeltaTime * Value * RotationSpeed;
		SetDesiredYaw(NewYaw);
	}
}

void URotationCameraComponent::SetDesiredYaw(const float NewYaw)
{
	SetDesiredYawValue(NewYaw);
	if(!bApplyLag)
	{
		TargetComponent->SetWorldRotation(GetDesiredRotationWithOffset());
	}
}

void URotationCameraComponent::RotateRoll(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewRollOffset = DesiredRotationOffset.Roll - LastDeltaTime * Value * RotationSpeed;
		SetDesiredRollOffset(NewRollOffset);
	}
	else
	{
		const float NewRoll = DesiredRotation.Roll - LastDeltaTime * Value * RotationSpeed;		
		SetDesiredRoll(NewRoll);
	}
}

void URotationCameraComponent::SetDesiredRoll(const float NewRoll)
{
	SetDesiredRollValue(NewRoll);
	if(!bApplyLag)
	{
		TargetComponent->SetWorldRotation(GetDesiredRotationWithOffset());
	}
}

void URotationCameraComponent::DebugTick(const float DeltaTime)
{
	Super::DebugTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Rotation: %s"), *DesiredRotation.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Rotation Offset: %s"), *DesiredRotationOffset.ToString()));
}
