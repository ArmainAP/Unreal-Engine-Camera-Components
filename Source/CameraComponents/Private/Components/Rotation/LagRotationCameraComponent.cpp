//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Components/Rotation/LagRotationCameraComponent.h"

void ULagRotationCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const float DeltaTimeCorrective = DeltaTime * GetTimeDilationCorrectiveValue();
	const FQuat TickDesiredRotation = FMath::QInterpTo(Owner->GetActorRotation().Quaternion(), GetDesiredRotationWithOffset(), DeltaTimeCorrective, RotationLagSpeed);
	Owner->SetActorRotation(TickDesiredRotation);
}

void ULagRotationCameraComponent::SetDesiredPitch(const float NewPitch)
{
	SetDesiredPitchValue(NewPitch);
}

void ULagRotationCameraComponent::SetDesiredYaw(const float NewYaw)
{
	SetDesiredYawValue(NewYaw);
}

void ULagRotationCameraComponent::SetDesiredRoll(const float NewRoll)
{
	SetDesiredRollValue(NewRoll);
}
