//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Components/Rotation/RotationCameraComponent.h"

void URotationCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDesiredRotation(Owner->GetActorRotation());
}

void URotationCameraComponent::RotatePitch(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewPitchOffset = DesiredRotationOffset.Pitch - GetTickMultiplier() * Value * RotateSpeed;
		SetDesiredPitchOffset(NewPitchOffset);
	}
	else
	{
		const float NewPitch = DesiredRotation.Pitch - GetTickMultiplier() * Value * RotateSpeed;
		SetDesiredPitch(NewPitch);
	}
}

void URotationCameraComponent::SetDesiredPitch(const float NewPitch)
{
	SetDesiredPitchValue(NewPitch);
	Owner->SetActorRotation(GetDesiredRotationWithOffset());
}

void URotationCameraComponent::RotateYaw(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewYawOffset = DesiredRotationOffset.Yaw - GetTickMultiplier() * Value * RotateSpeed;
		SetDesiredYawOffset(NewYawOffset);
	}
	else
	{
		const float NewYaw = DesiredRotation.Yaw - GetTickMultiplier() * Value * RotateSpeed;
		SetDesiredYaw(NewYaw);
	}
}

void URotationCameraComponent::SetDesiredYaw(const float NewYaw)
{
	SetDesiredYawValue(NewYaw);
	Owner->SetActorRotation(GetDesiredRotationWithOffset());
}

void URotationCameraComponent::RotateRoll(const float Value, const bool RotateOffset)
{
	if (RotateOffset)
	{
		const float NewRollOffset = DesiredRotationOffset.Roll - GetTickMultiplier() * Value * RotateSpeed;
		SetDesiredRollOffset(NewRollOffset);
	}
	else
	{
		const float NewRoll = DesiredRotation.Roll - GetTickMultiplier() * Value * RotateSpeed;		
		SetDesiredRoll(NewRoll);
	}
}

void URotationCameraComponent::SetDesiredRoll(const float NewRoll)
{
	SetDesiredRollValue(NewRoll);
	Owner->SetActorRotation(GetDesiredRotationWithOffset());
}

#if WITH_EDITORONLY_DATA
void URotationCameraComponent::DebugTick(const float DeltaTime)
{
	Super::DebugTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Rotation: %s"), *DesiredRotation.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Desired Rotation Offset: %s"), *DesiredRotationOffset.ToString()));
}
#endif