// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCameraComponent.h"
#include "Components/ActorComponent.h"
#include "InputReactiveCameraComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable, BlueprintType, ClassGroup=Camera, meta=(BlueprintSpawnableComponent))
class CAMERACOMPONENTS_API UInputReactiveCameraComponent : public UBaseCameraComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupInputReactiveCamera(USpringArmComponent* InSpringArmComponent, UCameraComponent* InCameraComponent);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleX(const float Value, const bool bApplyToCamera = true);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleY(const float Value, const bool bApplyToCamera = true);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleZoom(const FVector2D Input, const bool bRequireBothInputs);

protected:
	FORCEINLINE USceneComponent* GetTargetComponent(const bool bApplyToCamera) const
	{
		return bApplyToCamera ? Cast<USceneComponent>(CameraComponent) : Cast<USceneComponent>(SpringArmComponent);
	}

protected:
	UPROPERTY(BlueprintReadOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(BlueprintReadOnly)
	float InitialTargetArmLength;

	UPROPERTY(BlueprintReadOnly)
	float InitialCameraFOV;

	UPROPERTY(EditAnywhere, Category=Offset)
	FVector2D Offset2D = FVector2D(8, 12);

	UPROPERTY(EditAnywhere, Category=Offset)
	float OffsetTargetArmLength = 75.0f;
	
	UPROPERTY(EditAnywhere, Category=Offset)
	float OffsetFOV = 10.0f;

	UPROPERTY(EditAnywhere, Category=Interpolation)
	FVector2D InterpolationSpeed = FVector2D(1, 2);

	UPROPERTY(EditAnywhere, Category=Interpolation)
	float TargetArmLengthInterpolationSpeed = 3.0f;

	UPROPERTY(EditAnywhere, Category=Interpolation)
	float TargetFOVInterpolationSpeed = 3.0f;
};
