// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CameraComponentsFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CAMERACOMPONENTS_API UCameraComponentsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void RotateYawAroundPivot(URotationCameraComponent* InRotationCameraComponent, ULocationCameraComponent* InLocationCameraComponent, const FVector Pivot, const float Value);

	UFUNCTION(BlueprintCallable)
	static void RotatePitchAroundPivot(URotationCameraComponent* InRotationCameraComponent, ULocationCameraComponent* InLocationCameraComponent, const FVector Pivot, const float Value);

	UFUNCTION(BlueprintCallable)
	static void ZoomAtLocation(ULocationCameraComponent* InLocationCameraComponent, float Value, const FVector Location);

	UFUNCTION(BlueprintCallable)
	static void ZoomAtMousePosition(ULocationCameraComponent* InLocationCameraComponent, float Value, APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	static void FocusOnActor(URotationCameraComponent* InRotationCameraComponent,
	                  ULocationCameraComponent* InLocationCameraComponent, const AActor* TargetActor,
	                  float DistanceMultiplier = 1.0f);
};
