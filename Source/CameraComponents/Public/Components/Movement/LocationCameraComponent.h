// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseCameraComponent.h"
#include "Data/ValueConstraint.h"
#include "LocationCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAMERACOMPONENTS_API ULocationCameraComponent : public UBaseCameraComponent
{
	GENERATED_BODY()

public:
	virtual void Setup_Implementation(USceneComponent* InTargetComponent) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void DebugTick(const float DeltaTime) override;
		
	UFUNCTION(BlueprintCallable)
	void Move(const FVector& Direction);
	
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveUp(float Value);

	UFUNCTION(BlueprintCallable)
	void SetDesiredLocation(FVector NewLocation);

	UFUNCTION(BlueprintPure)
	FVector GetCorrectedDestinationFromRestrictions(FVector Destination) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	float GetMovementScale();

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent)
	float GetTerrainHeightAdaptationValue();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector DesiredLocation = FVector::ZeroVector;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MovementSpeed = 100.0f;

	UPROPERTY()
	bool bTerrainHeightAdaptation = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), meta=(EditCondition="bTerrainHeightAdaptation"))
	float DesiredGroundDistance = 100.0f;
	
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintX;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintY;
	
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FValueConstraint ConstraintZ;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Movement Scaling")
	FValueConstraint ScaleMovementSpeed;

	//	Distance from the ground at which the camera will move at the default speed.
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"), Category="Movement Scaling")
	float ScalingDistanceReference = 1.0f;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Movement Scaling", meta=(EditCondition="!bTraceGround"))
	float GroundLevel = 0.0f;

	//	If true, will trace down the Z Axis to find the nearest ground and override GroundLevel.
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Movement Scaling")
	bool bTraceGround = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category="Movement Scaling", meta=(EditCondition="bTraceGround"))
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceGroundChannels;
};
