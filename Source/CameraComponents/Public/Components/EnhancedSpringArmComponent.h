// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/ValueConstraint.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class CAMERACOMPONENTS_API UEnhancedSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DebugTick(const float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void Move(const FVector& Direction);
	
	// @param MoveSocketOffset - Set this to true to move the SocketOffset instead of the TargetOffset.
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value, bool bMoveSocketOffset = true);

	// @param MoveSocketOffset - Set this to true to move the SocketOffset instead of the TargetOffset.
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value, bool bMoveSocketOffset = true);

	// @param MoveSocketOffset - Set this to true to move the SocketOffset instead of the TargetOffset.
	UFUNCTION(BlueprintCallable)
	void MoveUp(float Value, bool bMoveSocketOffset = true);
	
	UFUNCTION(BlueprintCallable)
	void SetDesiredTargetOffset(FVector NewTargetOffset);
	
	UFUNCTION(BlueprintCallable)
	void SetDesiredSocketOffset(FVector NewSocketOffset);

	UFUNCTION(BlueprintNativeEvent)
	float GetMovementScale();

	UFUNCTION(BlueprintPure)
	FVector GetClampedOffset(FVector Offset) const;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResetTargetOffset() { SetDesiredTargetOffset(FVector::ZeroVector); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResetSocketOffset() { SetDesiredSocketOffset(FVector::ZeroVector); }

	UPROPERTY(BlueprintReadOnly)
	FVector DesiredSocketOffset;

	UPROPERTY(BlueprintReadOnly)
	FVector DesiredTargetOffset;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float OffsetSpeed = 100.0f;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintX;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintY;
	
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintZ;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Movement Scaling")
	FValueConstraint ScaleMovementSpeed;
	
	//	Zoom distance at which the camera will move at the default speed.
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.00001", UIMin = "0.00001"))
	float ScalingDistanceReference = 600.0f;

	UFUNCTION(BlueprintCallable)
	void ZoomIn(float Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetZoomInValue(float Value);

	UFUNCTION(BlueprintCallable)
	void SetDesiredZoom(const float NewZoom);

	UFUNCTION(BlueprintNativeEvent)
	float GetZoomInScale();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetZoomInValueAtDistance(float Value, float Distance = 0.f) const;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ZoomSpeed = 500.0f;

	UPROPERTY(BlueprintReadOnly, meta = (ClampMin = 0.0))
	float DesiredZoom;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.00001", UIMin = "0.00001"))
	float ScalingZoomReference = 500.0f;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintZoom;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Movement Scaling")
	FValueConstraint ScaleZoomSpeed;

	UPROPERTY()
	float LastDeltaTime = 0.f;
};
