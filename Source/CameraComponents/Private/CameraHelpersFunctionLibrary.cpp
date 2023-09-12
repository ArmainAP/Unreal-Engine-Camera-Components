// Copyright to Kat Code Labs, SRL. All Rights Reserved.


#include "CameraHelpersFunctionLibrary.h"

float UCameraHelpersFunctionLibrary::ClampValue(const float Value, const bool ConstrainMinimum, const float Minimum,
	const bool ConstrainMaximum, const float Maximum, const bool ReverseRestrictions)
{
	if (!(ConstrainMinimum || ConstrainMaximum)) return Value;

	if (ReverseRestrictions)
	{
		if (Value < Maximum && Value > Minimum)
		{
			return FMath::Abs(Value - Maximum) > FMath::Abs(Value - Minimum) ? Minimum : Maximum;
		}
		return Value;
	}
	
	return FMath::Clamp(Value, ConstrainMinimum ? Minimum : Value, ConstrainMaximum ? Maximum : Value);
}