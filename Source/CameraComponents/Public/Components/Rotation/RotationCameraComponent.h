//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseCameraComponent.h"
#include "Data/RotationConstraint.h"
#include "Kismet/KismetMathLibrary.h"
#include "RotationCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAMERACOMPONENTS_API URotationCameraComponent : public UBaseCameraComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override; 
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResetRotationOffset()
	{
		SetDesiredRotationOffset(FRotator::ZeroRotator);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDesiredRotationOffset(const FRotator NewRotationOffset)
	{
		DesiredRotationOffset = NewRotationOffset;
		SetDesiredRotation(DesiredRotation);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDesiredRotation(const FRotator NewRotation)
	{
		SetDesiredPitch(NewRotation.Pitch);
		SetDesiredYaw(NewRotation.Yaw);
		SetDesiredRoll(NewRotation.Roll);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FQuat GetDesiredRotationWithOffset() const
	{
		return FQuat(DesiredRotation + DesiredRotationOffset);
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetActiveConstraints(const bool bPitch, const bool bYaw, const bool bRoll)
	{
		PitchConstraint.bConstrainRotation = bPitch;
		YawConstraint.bConstrainRotation = bYaw;
		RollConstraint.bConstrainRotation = bRoll;
	}
	
	/////////////////
	// Begin Pitch //
	/////////////////
public:
	UFUNCTION(BlueprintCallable)
	void RotatePitch(const float Value, bool RotateOffset = false);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetDesiredPitch(const float NewPitch);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDesiredPitchOffset(const float NewPitchOffset)
	{
		DesiredRotationOffset.Pitch = NewPitchOffset;
		SetDesiredPitch(DesiredRotation.Pitch);
	}

	FORCEINLINE float GetClampedPitch(const float Pitch) const
	{
		return PitchConstraint.GetClampedValue(UKismetMathLibrary::NormalizeAxis(Pitch));
	}

protected:	
	FORCEINLINE void SetDesiredPitchValue(const float NewPitch)
	{
		DesiredRotation.Pitch = GetClampedPitch(NewPitch);
		DesiredRotationOffset.Pitch = GetClampedPitch(DesiredRotation.Pitch + DesiredRotationOffset.Pitch) - DesiredRotation.Pitch;
	}

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FRotationConstraint PitchConstraint;
	///////////////
	// End Pitch //
	///////////////

	///////////////
	// Begin Yaw //
	///////////////
public:
	UFUNCTION(BlueprintCallable)
	void RotateYaw(const float Value, bool RotateOffset = false);

	UFUNCTION(BlueprintCallable)
	virtual void SetDesiredYaw(const float NewYaw);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDesiredYawOffset(const float NewYawOffset)
	{
		DesiredRotationOffset.Yaw = NewYawOffset;
		SetDesiredYaw(DesiredRotation.Yaw);
	}
	
	FORCEINLINE float GetClampedYaw(const float Yaw) const
	{
		return YawConstraint.GetClampedValue(UKismetMathLibrary::NormalizeAxis(Yaw));
	}

protected:
	FORCEINLINE void SetDesiredYawValue(const float NewYaw)
	{
		DesiredRotation.Yaw = GetClampedYaw(NewYaw);
		DesiredRotationOffset.Yaw = GetClampedYaw(DesiredRotation.Yaw + DesiredRotationOffset.Yaw) - DesiredRotation.Yaw;
	}

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FRotationConstraint YawConstraint;
	/////////////
	// End Yaw //
	/////////////

	////////////////
	// Begin Roll //
	////////////////
public:
	UFUNCTION(BlueprintCallable)
	void RotateRoll(const float Value, bool RotateOffset = false);

	UFUNCTION(BlueprintCallable)
	virtual void SetDesiredRoll(const float NewRoll);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDesiredRollOffset(const float NewRollOffset)
	{
		DesiredRotationOffset.Roll = NewRollOffset;
		SetDesiredRoll(DesiredRotation.Roll);
	}
	
	FORCEINLINE float GetClampedRoll(const float Roll) const
	{
		return RollConstraint.GetClampedValue(UKismetMathLibrary::NormalizeAxis(Roll));
	}

protected:
	FORCEINLINE void SetDesiredRollValue(const float NewPitch)
	{
		DesiredRotation.Roll = GetClampedRoll(NewPitch);
		DesiredRotationOffset.Roll = GetClampedRoll(DesiredRotation.Roll + DesiredRotationOffset.Roll) - DesiredRotation.Roll;
	}
	
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category="Constraints")
	FRotationConstraint RollConstraint;
	//////////////
	// End Roll //
	//////////////
	
#if WITH_EDITORONLY_DATA
protected:
	virtual void DebugTick(const float DeltaTime) override;
#endif
	
protected:
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere)
	float RotateSpeed = 1.0f;

public: // TODO Refactor to protected?
	UPROPERTY(Interp, BlueprintReadOnly)
	FRotator DesiredRotation = FRotator::ZeroRotator;
	
	UPROPERTY(Interp, BlueprintReadOnly)
	FRotator DesiredRotationOffset = FRotator::ZeroRotator;
};
