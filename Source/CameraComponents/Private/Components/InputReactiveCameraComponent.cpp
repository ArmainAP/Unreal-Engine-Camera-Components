// Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "Components/InputReactiveCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

void UInputReactiveCameraComponent::HandleZoom_Implementation(FVector2D Input, bool bRequireBothInputs)
{
	if(!(IsValid(SpringArmComponent) && IsValid(CameraComponent)))
	{
		return;
	}

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const bool bZoom = bRequireBothInputs ? (Input.X != 0.0f && Input.Y != 0.0f) : (Input.X != 0.0f || Input.Y != 0.0f);

	const float TargetArmLength = bZoom ? InitialTargetArmLength + OffsetTargetArmLength : InitialTargetArmLength;
	SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetArmLength, DeltaTime, TargetArmLengthInterpolationSpeed);

	const float TargetFOV = bZoom ? InitialCameraFOV + OffsetFOV : InitialCameraFOV;
	CameraComponent->FieldOfView = FMath::FInterpTo(CameraComponent->FieldOfView, TargetFOV, DeltaTime, TargetFOVInterpolationSpeed);
}

void UInputReactiveCameraComponent::HandleX_Implementation(float Value, bool bApplyToCamera)
{
	USceneComponent* Component = GetTargetComponent(bApplyToCamera);
	if (!IsValid(Component))
	{
		return;
	}

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const FRotator CurrentRotation = Component->GetRelativeRotation();
	const FRotator TargetRotation = FRotator(Offset2D.X * Value, CurrentRotation.Yaw, CurrentRotation.Roll);
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpolationSpeed.X);
	Component->SetRelativeRotation(NewRotation);
}

void UInputReactiveCameraComponent::HandleY_Implementation(float Value, bool bApplyToCamera)
{
	USceneComponent* Component = GetTargetComponent(bApplyToCamera);
	if (!IsValid(Component))
	{
		return;
	}

	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const FRotator CurrentRotation = Component->GetRelativeRotation();
	const FRotator TargetRotation = FRotator(CurrentRotation.Pitch, Offset2D.Y * Value, CurrentRotation.Roll);
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpolationSpeed.Y);
	Component->SetRelativeRotation(NewRotation);
}

void UInputReactiveCameraComponent::SetupInputReactiveCamera_Implementation(USpringArmComponent* InSpringArmComponent,
	UCameraComponent* InCameraComponent)
{
	SpringArmComponent = InSpringArmComponent;
	CameraComponent = InCameraComponent;

	if(SpringArmComponent->IsValidLowLevel())
	{
		InitialTargetArmLength = SpringArmComponent->TargetArmLength;
	}

	if(CameraComponent)
	{
		InitialCameraFOV = CameraComponent->FieldOfView;
	}
}