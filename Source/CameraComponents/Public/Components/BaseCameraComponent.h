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
	
	/////////////////////////
	// Begin Time Dilation //
	/////////////////////////
protected:
	UPROPERTY(SaveGame, BlueprintReadWrite, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "Time Dilation")
	bool IgnoreTimeDilation = false;

	UPROPERTY()
	float LastTimeDilation = 1.f;
	
	FORCEINLINE float GetTimeDilationCorrectiveValue() const
	{
		return IgnoreTimeDilation ? 1.f / LastTimeDilation : 1.f;
	}
	
	FORCEINLINE float GetTickMultiplier() const
	{
		return GetWorld()->GetDeltaSeconds() * 100.f * GetTimeDilationCorrectiveValue();
	}
	///////////////////////
	// End Time Dilation //
	///////////////////////

	UPROPERTY()
	AActor* Owner;
};
