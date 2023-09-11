// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#include "Data/ValueConstraint.h"

#include "CameraHelpersFunctionLibrary.h"

float FValueConstraint::GetClampedValue(const float Value) const
{
	return UCameraHelpersFunctionLibrary::ClampValue(Value, bConstrainMinimum, Minimum, bConstrainMaximum, Maximum, bReverseRestriction);
}