//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "RotationConstraint.generated.h"

USTRUCT(BlueprintType)
struct CAMERACOMPONENTS_API FRotationConstraint
{
	GENERATED_BODY()

	// Rotation Constraint
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly)
	bool bConstrainRotation = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = bConstrainRotation))
	float MinimumRotation = -180.0f;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = bConstrainRotation))
	float MaximumRotation = 180.0f;

	// Useful if the rotation is around -180 / 180
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (EditCondition = bConstrainRotation))
	bool bReverseRotationRestriction = false;

	float GetClampedValue(float Value) const;
};
