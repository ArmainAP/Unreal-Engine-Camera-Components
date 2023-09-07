//Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCameraComponent.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent), ClassGroup=Camera)
class CAMERACOMPONENTS_API UBaseCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCameraComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Setup(USpringArmComponent* InSpringArmComponent, UCameraComponent* InCameraComponent);

protected:
	UPROPERTY(BlueprintReadOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadOnly)
	UCameraComponent* CameraComponent;
};
