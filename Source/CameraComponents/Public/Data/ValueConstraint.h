// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "ValueConstraint.generated.h"

USTRUCT(BlueprintType)
struct CAMERACOMPONENTS_API FValueConstraint
{
	GENERATED_BODY()
	
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere)
	bool bConstrainMinimum = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bConstrainMinimum))
	float Minimum = -180.0f;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere)
	bool bConstrainMaximum = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bConstrainMaximum))
	float Maximum = 180.0f;

	// Useful if the rotation is around -180 / 180
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (EditCondition ="bConstrainMinimum || bConstrainMaximum"))
	bool bReverseRestriction = false;

	float GetClampedValue(float Value) const;
};
