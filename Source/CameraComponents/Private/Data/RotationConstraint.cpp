//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Data/RotationConstraint.h"

float FRotationConstraint::GetClampedValue(const float Value) const
{
	if (!bConstrainRotation)
	{
		return Value;
	}

	if (bReverseRotationRestriction && Value < MaximumRotation && Value > MinimumRotation)
	{
		return FMath::Abs(Value - MaximumRotation) > FMath::Abs(Value - MinimumRotation) ? MinimumRotation : MaximumRotation;
	}

	return FMath::Clamp(Value, MinimumRotation, MaximumRotation);
}
