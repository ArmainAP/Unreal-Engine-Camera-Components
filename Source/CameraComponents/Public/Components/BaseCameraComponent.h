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

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#if WITH_EDITORONLY_DATA
	/////////////////
	// Begin Debug //
	/////////////////
protected:
	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	virtual void DebugTick(const float DeltaTime) {};
	///////////////
	// End Debug //
	///////////////
#endif

	UPROPERTY()
	float LastDeltaTime = 0.0f;
	
	UPROPERTY()
	AActor* Owner;
};
