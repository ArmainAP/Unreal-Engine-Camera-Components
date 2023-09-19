// Copyright to Kat Code Labs, SRL. All Rights Reserved.

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
	virtual void DebugTick(const float DeltaTime) {};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Setup(USceneComponent* InTargetComponent);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector GetTargetComponentLocation() const
	{
		if(!IsValid(TargetComponent))
		{
			return FVector::ZeroVector;
		}
		return TargetComponent->GetComponentLocation();
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector InverseTransformVectorNoScale(const FVector& InWorldVector) const
	{
		return TargetComponent->GetComponentTransform().InverseTransformVectorNoScale(InWorldVector);
	}

public:
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category=Lag)
	bool bApplyLag = false;

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category=Lag)
	float LagSpeed = 5.0f;

protected:
	UPROPERTY()
	float LastDeltaTime = 0.0f;
	
	UPROPERTY()
	USceneComponent* TargetComponent;

	UPROPERTY(EditAnywhere, Category=Debug)
	bool bDebug = false;
};
