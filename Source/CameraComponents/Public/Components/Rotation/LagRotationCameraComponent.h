//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Rotation/RotationCameraComponent.h"
#include "LagRotationCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAMERACOMPONENTS_API ULagRotationCameraComponent : public URotationCameraComponent
{
	GENERATED_BODY()

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetDesiredPitch(const float NewPitch) override;
	virtual void SetDesiredYaw(const float NewYaw) override;
	virtual void SetDesiredRoll(const float NewRoll) override;

protected:
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category=Lag)
	float RotationLagSpeed = 5.0f;
};
