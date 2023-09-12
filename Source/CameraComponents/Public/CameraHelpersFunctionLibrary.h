// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CameraHelpersFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CAMERACOMPONENTS_API UCameraHelpersFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float ClampValue(const float Value, const bool ConstrainMinimum, const float Minimum, const bool ConstrainMaximum, const float Maximum, const bool ReverseRestrictions = false);
};
