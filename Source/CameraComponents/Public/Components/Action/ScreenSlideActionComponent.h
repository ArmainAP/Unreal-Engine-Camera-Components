// Copyright to Kat Code Labs, SRL. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScreenSlideActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMERACOMPONENTS_API UScreenSlideActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScreenSlideActionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartScreenSlide();

	UFUNCTION(BlueprintCallable)
	void EndScreenSlide();

protected:
	UFUNCTION(BlueprintPure)
	FVector2D GetMousePositionRatio() const;

	// Max effective distance from initial cursor position
	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ScreenSlidingMaxRatio = 0.2f;

	UPROPERTY(BlueprintReadOnly)
	FVector2D ScreenSlidingOriginRatio;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateUpdated, FVector2D, Direction);

	UPROPERTY(BlueprintAssignable)
	FStateUpdated OnUpdateSliding;
};
